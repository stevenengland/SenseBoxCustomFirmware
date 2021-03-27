#pragma once

#include <ctime>

namespace Time
{
    class TimeConverter
    {
    public:
        virtual ~TimeConverter() = default;

        virtual void GetUtcTime(time_t epochTime, char* utcTimeOutput) = 0;
    };
}
