#pragma once

#include "IWatchDog.h"

namespace Time
{
    class ArduinoWatchDog final : public IWatchDog
    {
    public:
        int Enable(int milliseconds) override;
        void Disable() override;
        void Reset() override;
    };
}
