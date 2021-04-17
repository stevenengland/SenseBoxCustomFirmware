#pragma once

#include <gmock/gmock.h>
#include "ISensor.h"

namespace Sensor
{
    class SensorMock final : public ISensor
    {
    public:
        MOCK_METHOD(float, ReadValue, (), (override));
        MOCK_METHOD(bool, Init, (), (override));
    };
}