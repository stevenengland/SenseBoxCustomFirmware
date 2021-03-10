#pragma once

namespace SoundLevelMeter
{
    struct SoundLevelMeter
    {
        virtual ~SoundLevelMeter() = default;
        
        virtual float ReadValue() = 0;
    };
}
