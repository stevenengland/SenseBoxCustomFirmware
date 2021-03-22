#pragma once

#include <ctime>

namespace Time
{
    class TimeProvider
    {
    public:
        virtual ~TimeProvider() = default;

        virtual time_t GetEpochTime() = 0;
    };
}
