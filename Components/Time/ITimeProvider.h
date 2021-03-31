#pragma once

#include <ctime>

namespace Time
{
    class ITimeProvider
    {
    public:
        virtual ~ITimeProvider() = default;

        virtual time_t GetEpochTime() = 0;
    };
}
