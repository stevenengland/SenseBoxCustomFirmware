#pragma once

#include "IRamInfoReader.h"

namespace CentralUnit
{
    class RamInfoReader final : public IRamInfoReader
    {
    public:
        int GetFreeRamSize() override;
    };
}
