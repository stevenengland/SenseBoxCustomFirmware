#include "AnalogPortReader.h"

namespace Arduino
{
	float AnalogPortReader::ReadVoltageFromPin(int pin)
	{
        const float voltageValue = analogRead(pin);
        return voltageValue;
	}
}
