#pragma once

#include "TimeConverter.h"

namespace Time
{
    class StandardTimeConverter final : public TimeConverter
    {
    public:
        void GetUtcTime(time_t epochTime, char* utcTimeOutput) override;
    };
}
