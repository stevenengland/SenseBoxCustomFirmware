#pragma once

#include <gmock/gmock.h>
#include "AnalogPortReader.h"

namespace Connectivity
{
    namespace AnalogPorts
    {
        class AnalogPortReaderMock final : public AnalogPortReader
        {
        public:
            MOCK_METHOD(float, ReadVoltageFromPin, (int pin), (override));
        };
    }
}
