#pragma once

#include "AnalogPortReader.h"

namespace Arduino
{
    struct ArduinoAnalogPortReader final : public AnalogPortReader
    {
        float ReadVoltageFromPin(int pin) override;
    };
}
