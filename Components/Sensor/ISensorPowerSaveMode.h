#pragma once

namespace Sensor
{
    class ISensorPowerSaveMode
    {
    public:
        virtual ~ISensorPowerSaveMode() = default;

        virtual void Sleep() = 0;
        virtual void Wakeup() = 0;
    };
}
