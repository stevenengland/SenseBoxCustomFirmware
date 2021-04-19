#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../../Components/Sensor/NovaSds011.h"
#include "../Mocks/NovaSds011DriverMock.hpp"

using namespace testing;

namespace SensorTests
{
    class NovaSds011Should :public Test
    {
    protected:
        Sensor::NovaSds011DriverMock _novaSds011DriverMock;
        Sensor::NovaSds011 _sensor{ _novaSds011DriverMock };
    };

    TEST_F(NovaSds011Should, CallDriver_IfBeginIsCalled)
    {
        EXPECT_CALL(_novaSds011DriverMock, Begin()).Times(1);

        _sensor.Init();
    }

    TEST_F(NovaSds011Should, ReturnNan_IfWrongPhenomenonIdIsUsed)
    {
        const auto value = _sensor.ReadValue(2);

        ASSERT_TRUE(isnan(value));
    }

    TEST_F(NovaSds011Should, ReturnNanForP25_IfErrorOccurs)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1).WillOnce(SetArgReferee<2>(true));

        const auto value = _sensor.ReadValue();

        ASSERT_TRUE(isnan(value));
    }

    TEST_F(NovaSds011Should, ReturnNanForP10_IfErrorOccurs)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1).WillOnce(SetArgReferee<2>(true));

        const auto value = _sensor.ReadValue(1);

        ASSERT_TRUE(isnan(value));
    }

    TEST_F(NovaSds011Should, ReadP25_WhenSinglePhenomenonWasQueried)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1)
            .WillOnce(DoAll(SetArgReferee<0>(1.0f), SetArgReferee<1>(2.0f), SetArgReferee<2>(false)));

        const auto value = _sensor.ReadValue();

        ASSERT_FLOAT_EQ(1.0f, value);
    }

    TEST_F(NovaSds011Should, ReadP10_WhenSinglePhenomenonWasQueried)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1)
            .WillOnce(DoAll(SetArgReferee<0>(2.0f), SetArgReferee<1>(1.0f), SetArgReferee<2>(false)));

        const auto value = _sensor.ReadValue(1);

        ASSERT_FLOAT_EQ(1.0f, value);
    }

    TEST_F(NovaSds011Should, ReadAllPhenomenons_WhenAllPhenomenonWereQueried)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1)
            .WillOnce(DoAll(SetArgReferee<0>(1.0f), SetArgReferee<1>(2.0f), SetArgReferee<2>(false)));

        const auto values = _sensor.ReadValues();

        ASSERT_FLOAT_EQ(1.0f, values.Reads[0]);
        ASSERT_FLOAT_EQ(2.0f, values.Reads[1]);
    }

    TEST_F(NovaSds011Should, ReturnNanForAllPhenomenons_WhenAllPhenomenonWereQueriedAndErrorOccurs)
    {
        EXPECT_CALL(_novaSds011DriverMock, Read(_, _, _)).Times(1)
            .WillOnce(DoAll(SetArgReferee<0>(1.0f), SetArgReferee<1>(2.0f), SetArgReferee<2>(true)));

        const auto values = _sensor.ReadValues();

        ASSERT_TRUE(isnan(values.Reads[0]));
        ASSERT_TRUE(isnan(values.Reads[1]));
    }
}
