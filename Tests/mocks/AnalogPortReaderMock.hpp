#pragma once

#include <gmock/gmock.h>
#include "IAnalogPortReader.h"

namespace Peripherals
{
    class AnalogPortReaderMock final : public IAnalogPortReader
    {
    public:
        MOCK_METHOD(float, ReadVoltageFromPin, (int pin), (override));
    };
}
