#pragma once

#include "TimeConverter.h"

namespace Time
{
    class StandardTimeConverter final : public TimeConverter
    {
    public:
        char* GetUtcTime(time_t epochTime) override;
    };
}
