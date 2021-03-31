#pragma once

#include "IAnalogPortReader.h"

namespace Peripherals
{
    class SenseBoxAnalogPortReader final : public IAnalogPortReader
    {
    public:
        float ReadVoltageFromPin(int pin) override;
    };
}