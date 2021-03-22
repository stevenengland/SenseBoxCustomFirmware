#pragma once

#include <ctime>

namespace Time
{
    static char StrBuffer[35]; ///< @brief Temporary buffer for time and date strings

    class TimeConverter
    {
    public:
        virtual ~TimeConverter() = default;

        virtual char* GetUtcTime(time_t epochTime) = 0;
    };
}
