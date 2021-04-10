#pragma once

#include <ctime>

namespace Measurement
{
    typedef struct
    {
        const char* SensorId;
        float Value;
        time_t Timestamp;
    } Measurement;
}
