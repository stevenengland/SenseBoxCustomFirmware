#pragma once

#include "ISenseBoxIoMapper.h"

namespace Peripherals
{
    class SenseBoxIoMapper final : public ISenseBoxIoMapper

    {
    public:
        void PowerAll() override;
    };
}