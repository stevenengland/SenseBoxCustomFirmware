#pragma once

#include "IElapsedTimeProvider.h"

namespace Time
{
    class ArduinoElapsedTimeProvider final : public IElapsedTimeProvider
    {
    public:
        unsigned long ElapsedMilliseconds() override;
        void WaitSync(int milliseconds) override;
    };
}
