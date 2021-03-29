#include "Timer.h"

namespace Time
{
    Timer::Timer(ElapsedTimeProvider& elapsedTimeProvider, const long interval)
        : _elapsedTimeProvider(elapsedTimeProvider), _interval(interval)
    {
    }

    bool Timer::HasIntervalElapsed()
    {
        _timeNow = _elapsedTimeProvider.ElapsedMilliseconds();
        if (_timeNow > _timeLastRun + _interval) {
            _timeLastRun = _timeNow;
            return true;
        }

        return false;
    }

    void Timer::SetInterval(const long interval)
    {
        _interval = interval;
    }


}
