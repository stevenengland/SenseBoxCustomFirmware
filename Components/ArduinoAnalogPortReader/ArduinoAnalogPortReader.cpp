#include "ArduinoAnalogPortReader.h"

namespace Arduino
{
    float ArduinoAnalogPortReader::ReadVoltageFromPin(int pin)
    {
        const float voltageValue = analogRead(pin);
        return voltageValue;
    }
}
