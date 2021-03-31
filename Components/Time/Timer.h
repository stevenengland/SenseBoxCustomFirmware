#pragma once

#include "IElapsedTimeProvider.h"

namespace Time
{
    class Timer
    {
    public:
        explicit Timer(IElapsedTimeProvider& elapsedTimeProvider, long interval);

        void SetInterval(long interval);
        bool HasIntervalElapsed();
    private:
        IElapsedTimeProvider& _elapsedTimeProvider;
        unsigned long _interval = 1000;
        unsigned long _timeNow = 0;
        unsigned long _timeLastRun = 0;
    };
}
