#include "StandardTimeConverter.h"

#include <time.h>
#include <string.h>

namespace Time
{
    void StandardTimeConverter::GetUtcTime(time_t epochTime, char* utcTimeOutput)
    {
        struct tm* dt = gmtime(&epochTime);
        char strBuffer[35]{};
        auto timeLength = strftime(strBuffer, sizeof(strBuffer), "%Y-%m-%dT%H:%M:%SZ", dt) + 1;
        strncpy(utcTimeOutput, strBuffer, timeLength);
    }
}
