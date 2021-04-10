#include "../../Components/Measurement/MeasurementManager.h"
#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../Mocks/MeasurementAggregationStrategyMock.hpp"
#include "../Mocks/MeasurementContainerMock.hpp"
#include "../Mocks/TimeConverterMock.hpp"

using namespace testing;

namespace MeasurementManagerTests
{
    class MeasurementManagerShould : public Test
    {
    protected:
        Measurement::MeasurementContainerMock _container;
        Measurement::MeasurementAggregationStrategyMock _aggregationStrategy;
        Measurement::MeasurementManager _manager
        {
            _container,
            _aggregationStrategy,
            3,
            "TestSensor"
        };
    };

    TEST_F(MeasurementManagerShould, NotAddMeasurementToContainer_WhenIntervalHasNotElapsedYet)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(0);

        _manager.Record(3, 101);
        _manager.Record(1, 102);
    }

    TEST_F(MeasurementManagerShould, AddMeasurementToContainer_WhenIntervalElapsed)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1);

        _manager.Record(3, 101);
        _manager.Record(1, 102);
        _manager.Record(4, 104);
    }

    TEST_F(MeasurementManagerShould, AddMeasurementToContainer_AfterIntervalDurationWasChangedAndIntervalElapsed)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1);

        _manager.SetInterval(1);

        _manager.Record(3, 101);
        _manager.Record(1, 101);
        _manager.Record(4, 102);
    }

    TEST_F(MeasurementManagerShould, NotAddMeasurementToContainer_AfterIntervalDurationWasChangedAndIntervalDidNotElapseYet)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(0);

        _manager.SetInterval(1);

        _manager.Record(3, 101);
        _manager.Record(1, 101);
        _manager.Record(4, 101);
    }

    TEST_F(MeasurementManagerShould, RecordForEveryCall_IfIntervalIsSetToZero)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(3);

        _manager.SetInterval(0);

        _manager.Record(3, 101);
        _manager.Record(1, 101);
        _manager.Record(4, 101);
    }

    TEST_F(MeasurementManagerShould, AddSpecificMeasurementToContainer_WhenIntervalElapsed)
    {
        //char dateString[] = "2018-02-01T23:18:02Z";
        Measurement::Measurement measurment;
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1)
            .WillOnce(SaveArg<0>(&measurment));
        //EXPECT_CALL(_timeConverter, GetUtcTime(_, _))
        //    .Times(1)
        ////.WillOnce(SetArgPointee<1>(ByRef(dateString)));
        //.WillOnce(SetArrayArgument<1>(dateString, dateString + strlen(dateString) + 1));
        EXPECT_CALL(_aggregationStrategy, Aggregate(_,_))
            .Times(3)
            .WillOnce(Return(3.0f))
            .WillOnce(Return(2.0f)) // This one is returned
            .WillOnce(Return(1.0f));

        _manager.Record(3, 101);
        _manager.Record(1, 102);
        _manager.Record(4, 104);

        ASSERT_STREQ("TestSensor", measurment.SensorId);
        ASSERT_EQ(101, measurment.Timestamp);
        ASSERT_FLOAT_EQ(2.0f, measurment.Value);
    }
}
