#pragma once
#include "SensorReads.h"

namespace Sensor
{
    struct ISensor
    {
        virtual ~ISensor() = default;
        
        virtual float ReadValue(int phenomenonId = 0) = 0;
        virtual SensorReads ReadValues() = 0;
        virtual bool Init() = 0;
    };
}
