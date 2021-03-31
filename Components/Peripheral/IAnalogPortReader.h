#pragma once

namespace Peripherals
{
    struct IAnalogPortReader
    {
        virtual ~IAnalogPortReader() = default;

        virtual float ReadVoltageFromPin(int pin) = 0;
    };
}
