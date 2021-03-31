#include "SenseBoxAnalogPortReader.h"
#include "Arduino.h"

namespace Peripherals
{
    float SenseBoxAnalogPortReader::ReadVoltageFromPin(int pin)
    {
        const float voltageValue = analogRead(pin);
        return voltageValue;
    }
}
