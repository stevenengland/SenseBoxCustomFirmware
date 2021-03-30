#pragma once

namespace Time
{
    class IWatchDog
    {
    public:
        virtual ~IWatchDog() = default;

        virtual int Enable(int milliseconds) = 0;
        virtual void Disable() = 0;
        virtual void Reset() = 0;
    };
}
