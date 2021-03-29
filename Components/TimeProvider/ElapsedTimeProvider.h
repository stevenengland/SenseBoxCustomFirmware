#pragma once

namespace Time
{
    class ElapsedTimeProvider
    {
    public:
        virtual ~ElapsedTimeProvider() = default;

        virtual unsigned long ElapsedMilliseconds() = 0;
        virtual void WaitSync(int milliseconds) = 0;
    };
}
