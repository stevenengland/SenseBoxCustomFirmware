#pragma once

#include "ITimeConverter.h"

namespace Time
{
    class TimeConverter final : public ITimeConverter
    {
    public:
        void GetUtcTime(time_t epochTime, char* utcTimeOutput) override;
    };
}
