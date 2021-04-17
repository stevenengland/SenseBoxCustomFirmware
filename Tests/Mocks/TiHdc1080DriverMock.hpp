#pragma once

#include <gmock.h>

#include "../../Components/Sensor/ITiHdc1080Driver.h"

namespace Sensor
{
    class TiHdc1080DriverMock final : public ITiHdc1080Driver
    {
    public:
        MOCK_METHOD(void, Begin, (), (override));
        MOCK_METHOD(float, ReadTemperature, (), (override));
        MOCK_METHOD(float, ReadHumidity, (), (override));
    };
}
