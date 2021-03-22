#include "StandardTimeConverter.h"

#include <ctime>

namespace Time
{
    char* StandardTimeConverter::GetUtcTime(time_t epochTime)
    {
        struct tm dt;
        gmtime_s(&dt, &epochTime);
        strftime(StrBuffer, sizeof(StrBuffer), "%Y-%m-%dT%H:%M:%SZ", &dt);
        return StrBuffer;
    }
}
