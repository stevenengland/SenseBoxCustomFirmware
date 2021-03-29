#pragma once

namespace Measurement
{
    typedef struct
    {
        const char* SensorId;
        float Value;
        const char* Timestamp;
    } Measurement;
}
