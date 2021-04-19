#pragma once

namespace Sensor
{
    class INovaSds011Driver
    {
    public:
        virtual ~INovaSds011Driver() = default;

        virtual void Begin() = 0;
        virtual void Read(float& p25, float& p10, bool& error) = 0;
    };
}
