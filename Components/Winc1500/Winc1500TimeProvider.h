#include "TimeProvider.h"

namespace Time
{
    class Winc1500TimeProvider final : public TimeProvider
    {
    public:
        time_t GetEpochTime() override;
    };
}
