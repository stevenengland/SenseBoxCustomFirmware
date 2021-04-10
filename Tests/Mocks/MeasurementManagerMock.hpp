#pragma once

#include <gmock/gmock.h>
#include "IMeasurementManager.h"

using namespace testing;

namespace Measurement
{
    class MeasurementManagerMock final : public  IMeasurementManager
    {
    public:
        MOCK_METHOD(void, Record, (float value, time_t measurementTime),(override));
        MOCK_METHOD(void, SetInterval, (time_t interval), (override));
    };
}
