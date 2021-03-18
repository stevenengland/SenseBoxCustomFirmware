#include "SenseBoxAnalogPortReader.h"
#include "Arduino.h"

namespace Connectivity
{
    namespace AnalogPorts
    {
        float SenseBoxAnalogPortReader::ReadVoltageFromPin(int pin)
        {
            const float voltageValue = analogRead(pin);
            return voltageValue;
        }
    }
}
