#pragma once

#include <gmock.h>
#include "IRamInfoReader.h"

namespace CentralUnit
{
    class RamInfoReaderMock final : public IRamInfoReader
    {
    public:
        MOCK_METHOD(int, GetFreeRamSize, (), (override));
    };
}
