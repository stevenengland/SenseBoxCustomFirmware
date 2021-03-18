#pragma once

#include "AnalogPortReader.h"

namespace Connectivity
{
    namespace AnalogPorts
    {
        class SenseBoxAnalogPortReader final : public AnalogPortReader
        {
        public:
            float ReadVoltageFromPin(int pin) override;
        };
    }
}