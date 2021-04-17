#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../../Components/Sensor/TiHdc1080Humidity.h"
#include "../Mocks/TiHdc1080DriverMock.hpp"

using namespace testing;

namespace HumiditySensorTests
{
    class TiHdc1080HumidityShould : public Test
    {
    protected:
        Sensor::TiHdc1080DriverMock _tiHdc1080DriverMock;
        Sensor::TiHdc1080Humidity _sensor{ _tiHdc1080DriverMock };
    };

    TEST_F(TiHdc1080HumidityShould, CallDriver_IfBeginIsCalled)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, Begin()).Times(1);

        _sensor.Init();
    }

    TEST_F(TiHdc1080HumidityShould, CallDriver_IfReadValueIsCalled)
    {
        EXPECT_CALL(_tiHdc1080DriverMock, ReadHumidity()).Times(1);

        _sensor.ReadValue();
    }
}
