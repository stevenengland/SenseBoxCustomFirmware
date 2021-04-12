#pragma once

#include <ctime>

namespace Sketch
{
    typedef struct
    {
        // Component - Feature - Config
        int TimeProvider_TimeRequest_RetryInterval;
        int TimeProvider_TimeRequest_RetryCount;

        int WatchDog_KeepAlive_TimeoutInterval;

        int Sensor_Measure_Interval;

        int SoundLevelMeter_Measure_Interval;

        int Osem_Upload_Interval;
    } SketchConfiguration;
}