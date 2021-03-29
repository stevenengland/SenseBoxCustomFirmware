#pragma once

#include "ElapsedTimeProvider.h"

namespace Time
{
    class ArduinoElapsedTimeProvider final : public ElapsedTimeProvider
    {
    public:
        unsigned long ElapsedMilliseconds() override;
        void WaitSync(int milliseconds) override;
    };
}
