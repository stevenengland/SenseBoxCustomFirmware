#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../../Components/Sensor/TiHdc1080.h"
#include "../Mocks/TiHdc1080DriverMock.hpp"

using namespace testing;

namespace SensorTests
{
    class TiHdc1080Should :public Test
    {
    protected:
        Sensor::TiHdc1080DriverMock _tiHdc1080DriverMock;
        Sensor::TiHdc1080 _sensor{ _tiHdc1080DriverMock };
    };

    TEST_F(TiHdc1080Should, CallDriver_IfBeginIsCalled)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, Begin()).Times(1);

        _sensor.Init();
    }

    TEST_F(TiHdc1080Should, ReturnNan_IfWrongPhenomenonIdIsUsed)
    {
        const auto value = _sensor.ReadValue(2);

        // Assert
        ASSERT_TRUE(isnan(value));
    }

    TEST_F(TiHdc1080Should, ReadTemperature_WhenSinglePhenomenonWasQueried)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, ReadTemperature()).Times(1).WillOnce(Return(1.0f));

        const auto value = _sensor.ReadValue();

        ASSERT_FLOAT_EQ(1.0f, value);
    }

    TEST_F(TiHdc1080Should, ReadHumidity_WhenSinglePhenomenonWasQueried)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, ReadHumidity()).Times(1).WillOnce(Return(1.0f));

        const auto value = _sensor.ReadValue(1);

        ASSERT_FLOAT_EQ(1.0f, value);
    }

    TEST_F(TiHdc1080Should, ReadAllPhenomenons_WhenAllPhenomenonWereQueried)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, ReadTemperature()).Times(1).WillOnce(Return(1.0f));
        EXPECT_CALL(_tiHdc1080DriverMock, ReadHumidity()).Times(1).WillOnce(Return(2.0f));

        const auto values = _sensor.ReadValues();

        ASSERT_FLOAT_EQ(1.0f, values.Reads[0]);
        ASSERT_FLOAT_EQ(2.0f, values.Reads[1]);
    }
}
