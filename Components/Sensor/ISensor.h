#pragma once

namespace Sensor
{
    struct ISensor
    {
        virtual ~ISensor() = default;
        
        virtual float ReadValue() = 0;
        virtual bool Init() = 0;
    };
}
