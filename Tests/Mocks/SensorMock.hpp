#pragma once

#include <gmock/gmock.h>
#include "ISensor.h"

namespace Sensor
{
    class SensorMock final : public ISensor
    {
    public:
        MOCK_METHOD(bool, Init, (), (override));
        MOCK_METHOD(float, ReadValue, (int phenomenonId), (override));
        MOCK_METHOD(SensorReads, ReadValues, (), (override));
    };
}
