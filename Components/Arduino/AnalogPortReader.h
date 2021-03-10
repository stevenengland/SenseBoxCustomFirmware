#pragma once

namespace Arduino
{
	struct AnalogPortReader
	{
		virtual ~AnalogPortReader() = default;
		
		virtual float ReadVoltageFromPin(int pin) = 0;
	};
}
