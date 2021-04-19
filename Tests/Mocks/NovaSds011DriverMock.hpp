#pragma once

#include <gmock.h>

#include "../../Components/Sensor/INovaSds011Driver.h"

namespace Sensor
{
    class NovaSds011DriverMock final : public INovaSds011Driver
    {
    public:
        MOCK_METHOD(void, Begin, (), (override));
        MOCK_METHOD(void, Read, (float& p25, float& p10, bool& error), (override));
    };
}