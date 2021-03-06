#pragma once

#include <ctime>

namespace Measurement
{
    class IMeasurementRecorder
    {
    public:
        virtual ~IMeasurementRecorder() = default;

        virtual void Record(float value, time_t measurementTime) = 0;
        virtual void SetInterval(time_t interval) = 0;
    };
}
