#pragma once

#include <gmock/gmock.h>
#include "ArduinoAnalogPortReader.h"

namespace Arduino
{
    class AnalogPortReaderMock final : public AnalogPortReader
    {
    public:
        MOCK_METHOD(float, ReadVoltageFromPin, (int pin), (override));
    };
}
