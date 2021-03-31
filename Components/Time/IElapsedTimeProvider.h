#pragma once

namespace Time
{
    class IElapsedTimeProvider
    {
    public:
        virtual ~IElapsedTimeProvider() = default;

        virtual unsigned long ElapsedMilliseconds() = 0;
        virtual void WaitSync(int milliseconds) = 0;
    };
}
