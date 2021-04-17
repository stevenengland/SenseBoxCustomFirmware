#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../../Components/Sensor/TiHdc1080Temperature.h"
#include "../Mocks/TiHdc1080DriverMock.hpp"

using namespace testing;

namespace TemperatureSensorTests
{
    class TiHdc1080TemperatureShould :public Test
    {
    protected:
        Sensor::TiHdc1080DriverMock _tiHdc1080DriverMock;
        Sensor::TiHdc1080Temperature _sensor{ _tiHdc1080DriverMock };
    };

    TEST_F(TiHdc1080TemperatureShould, CallDriver_IfBeginIsCalled)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, Begin()).Times(1);

        _sensor.Init();
    }

    TEST_F(TiHdc1080TemperatureShould, CallDriver_IfReadValueIsCalled)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, ReadTemperature()).Times(1);

        _sensor.ReadValue();
    }
}
