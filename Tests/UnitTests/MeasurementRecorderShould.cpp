#include "../../Components/Measurement/MeasurementRecorder.h"
#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../Mocks/MeasurementAggregationStrategyMock.hpp"
#include "../Mocks/MeasurementContainerMock.hpp"
#include "../Mocks/TimeConverterMock.hpp"

using namespace testing;

namespace MeasurementTests
{
    class MeasurementRecorderShould : public Test
    {
    protected:
        Measurement::MeasurementContainerMock _container;
        Measurement::MeasurementAggregationStrategyMock _aggregationStrategy;
        Measurement::MeasurementRecorder _recorder
        {
            _container,
            _aggregationStrategy,
            3,
            "TestSensor"
        };
    };

    TEST_F(MeasurementRecorderShould, NotAddMeasurementToContainer_WhenIntervalHasNotElapsedYet)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(0);

        _recorder.Record(3, 101);
        _recorder.Record(1, 102);
    }

    TEST_F(MeasurementRecorderShould, AddMeasurementToContainer_WhenIntervalElapsed)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1);

        _recorder.Record(3, 101);
        _recorder.Record(1, 102);
        _recorder.Record(4, 104);
    }

    TEST_F(MeasurementRecorderShould, AddMeasurementToContainer_AfterIntervalDurationWasChangedAndIntervalElapsed)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1);

        _recorder.SetInterval(1);

        _recorder.Record(3, 101);
        _recorder.Record(1, 101);
        _recorder.Record(4, 102);
    }

    TEST_F(MeasurementRecorderShould, NotAddMeasurementToContainer_AfterIntervalDurationWasChangedAndIntervalDidNotElapseYet)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(0);

        _recorder.SetInterval(1);

        _recorder.Record(3, 101);
        _recorder.Record(1, 101);
        _recorder.Record(4, 101);
    }

    TEST_F(MeasurementRecorderShould, RecordForEveryCall_IfIntervalIsSetToZero)
    {
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(3);

        _recorder.SetInterval(0);

        _recorder.Record(3, 101);
        _recorder.Record(1, 101);
        _recorder.Record(4, 101);
    }

    TEST_F(MeasurementRecorderShould, AddSpecificMeasurementToContainer_WhenIntervalElapsed)
    {
        //char dateString[] = "2018-02-01T23:18:02Z";
        Measurement::Measurement measurment;
        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(1)
            .WillOnce(SaveArg<0>(&measurment));

        EXPECT_CALL(_aggregationStrategy, Aggregate(_))
            .Times(3)
            .WillOnce(Return(3.0f))
            .WillOnce(Return(2.0f)) // This one is returned
            .WillOnce(Return(1.0f));

        _recorder.Record(3, 101);
        _recorder.Record(1, 102);
        _recorder.Record(4, 104);

        ASSERT_STREQ("TestSensor", measurment.SensorId);
        ASSERT_EQ(101, measurment.Timestamp);
        ASSERT_FLOAT_EQ(2.0f, measurment.Value);
    }

    TEST_F(MeasurementRecorderShould, AddSpecificMeasurementsToContainer_WhenIntervalElapsedMultipleTimes)
    {
        _recorder.SetInterval(1);
        Measurement::Measurement measurment1{};
        Measurement::Measurement measurment2{};
        Measurement::Measurement measurment3{};

        EXPECT_CALL(_container, AddMeasurement(_))
            .Times(3)
            .WillOnce(SaveArg<0>(&measurment1))
            .WillOnce(SaveArg<0>(&measurment2))
            .WillOnce(SaveArg<0>(&measurment3));
        
        EXPECT_CALL(_aggregationStrategy, Aggregate(_))
            .Times(10)
            .WillOnce(Return(5.0f))
            .WillOnce(Return(6.0f))
            .WillOnce(Return(4.0f)) //<- That one is last and therefore highest value before new interval begins...
            .WillOnce(Return(8.0f))
            .WillOnce(Return(9.0f))
            .WillOnce(Return(7.0f)) //<- That one is last and therefore highest value before new interval begins...
            .WillOnce(Return(2.0f))
            .WillOnce(Return(3.0f))
            .WillOnce(Return(1.0f)) //<- That one is last and therefore highest value before new interval begins...
            .WillOnce(Return(7.0f));

        _recorder.Record(1, 100);
        _recorder.Record(1, 100);
        _recorder.Record(1, 100);
        _recorder.Record(1, 101);
        _recorder.Record(1, 101);
        _recorder.Record(1, 101);
        _recorder.Record(1, 102);
        _recorder.Record(1, 102);
        _recorder.Record(1, 102);
        _recorder.Record(1, 103);

        ASSERT_STREQ("TestSensor", measurment1.SensorId);
        ASSERT_EQ(100, measurment1.Timestamp);
        ASSERT_FLOAT_EQ(4.0f, measurment1.Value);
        ASSERT_STREQ("TestSensor", measurment2.SensorId);
        ASSERT_EQ(101, measurment2.Timestamp);
        ASSERT_FLOAT_EQ(7.0f, measurment2.Value);
        ASSERT_STREQ("TestSensor", measurment3.SensorId);
        ASSERT_EQ(102, measurment3.Timestamp);
        ASSERT_FLOAT_EQ(1.0f, measurment3.Value);
    }

    TEST_F(MeasurementRecorderShould, ResetAggregationStrategy_IfNewIntervalBegins)
    {
        EXPECT_CALL(_aggregationStrategy, Reset())
            .Times(3);

        _recorder.SetInterval(1);

        _recorder.Record(3, 101);
        _recorder.Record(1, 102);
        _recorder.Record(4, 103);
        _recorder.Record(4, 104);
    }

    TEST_F(MeasurementRecorderShould, AggregateValueOnce_BeforeAddingAMeasurement_IfIntervalIsZero)
    {
        InSequence s;
        EXPECT_CALL(_aggregationStrategy, Aggregate(_)).Times(1);
        EXPECT_CALL(_container, AddMeasurement(_)).Times(1);

        _recorder.SetInterval(0);

        _recorder.Record(3, 101);
    }

    TEST_F(MeasurementRecorderShould, AggregateValueOnce_IfIntervalIsNotZero)
    {
        EXPECT_CALL(_aggregationStrategy, Aggregate(_)).Times(1);

        _recorder.Record(3, 101);
    }

    TEST_F(MeasurementRecorderShould, AddMeasurementWithValueNeqZero_IfIntervalIsZero)
    {
        Measurement::Measurement measurment{};
        _recorder.SetInterval(0);
        EXPECT_CALL(_aggregationStrategy, Aggregate(_)).WillOnce(Return(5.0f));
        EXPECT_CALL(_container, AddMeasurement(_)).WillOnce(SaveArg<0>(&measurment));

        _recorder.Record(3, 101);

        ASSERT_FLOAT_EQ(5.0f, measurment.Value);
    }
}
