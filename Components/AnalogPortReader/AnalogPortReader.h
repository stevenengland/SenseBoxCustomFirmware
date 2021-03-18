#pragma once

namespace Connectivity
{
    namespace AnalogPorts
    {
        struct AnalogPortReader
        {
            virtual ~AnalogPortReader() = default;

            virtual float ReadVoltageFromPin(int pin) = 0;
        };
    }
}
