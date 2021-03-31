#pragma once

namespace SoundLevelMeter
{
    struct ISoundLevelMeter
    {
        virtual ~ISoundLevelMeter() = default;
        
        virtual float ReadValue() = 0;
    };
}
