#pragma once

namespace Sensor
{
    struct ISensorPowerSaveMode
    {
        virtual ~ISensorPowerSaveMode() = default;

        virtual void Sleep() = 0;
        virtual void Wakeup() = 0;
    };
}
