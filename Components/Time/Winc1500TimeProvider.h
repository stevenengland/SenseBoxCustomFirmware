#pragma once

#include "ITimeProvider.h"

namespace Time
{
    class Winc1500TimeProvider final : public ITimeProvider
    {
    public:
        time_t GetEpochTime() override;
    };
}
