#include "WiFi101.h"
#include "Winc1500TimeProvider.h"

namespace Time
{
    time_t Winc1500TimeProvider::GetEpochTime()
    {
        return WiFi.getTime();
    }
}
