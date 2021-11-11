#pragma once

#include <gmock/gmock.h>
#include "IHibernatableSensor.h"

namespace Sensor
{
    class HibernatableSensorMock final : public IHibernatableSensor
    {
    public:
        MOCK_METHOD(bool, Init, (), (override));
        MOCK_METHOD(float, ReadValue, (int phenomenonId), (override));
        MOCK_METHOD(SensorReads, ReadValues, (), (override));
        MOCK_METHOD(void, Sleep, (), (override));
        MOCK_METHOD(void, Wakeup, (), (override));
    };
}
