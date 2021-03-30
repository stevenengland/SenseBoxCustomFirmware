#pragma once

#include <ctime>

namespace Time
{
    class ITimeConverter
    {
    public:
        virtual ~ITimeConverter() = default;

        virtual void GetUtcTime(time_t epochTime, char* utcTimeOutput) = 0;
    };
}
