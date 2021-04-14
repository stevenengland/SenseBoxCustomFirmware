#pragma once

#include <ctime>

namespace Sketch
{
    typedef struct
    {
        // Component - Feature - Config
        int Logger_LogLevel;

        int TimeProvider_TimeRequest_RetryInterval;
        int TimeProvider_TimeRequest_RetryCount;

        int NetworkProvider_ConnectionRequest_RetryInterval;
        int NetworkProvider_ConnectionRequest_RetryCount;

        int WatchDog_KeepAlive_TimeoutInterval;

        int MeasurementContainer_Capacity;

        int Sensor_Measure_Interval;

        int SoundLevelMeter_Measure_Interval;

        int Osem_Upload_Interval;
    } SketchConfiguration;
}