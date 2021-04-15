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
        int NetworkProvider_ConnectionStatus_CheckInterval;

        int WatchDog_KeepAlive_TimeoutInterval;

        int MeasurementContainer_Capacity;

        int Sensor_Measure_Interval;

        int SoundLevelMeter_Measure_Interval;
        int SoundLevelMeter_Measure_AggregationInterval;

        int Osem_Upload_Interval;

        int HealthCheck_Interval;
    } SketchConfiguration;
}