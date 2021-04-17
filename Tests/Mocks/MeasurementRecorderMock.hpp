#pragma once

#include <gmock/gmock.h>
#include "IMeasurementRecorder.h"

using namespace testing;

namespace Measurement
{
    class MeasurementRecorderMock final : public  IMeasurementRecorder
    {
    public:
        MOCK_METHOD(void, Record, (float value, time_t measurementTime),(override));
        MOCK_METHOD(void, SetInterval, (time_t interval), (override));
    };
}
