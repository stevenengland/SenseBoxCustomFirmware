#include "Timer.h"

namespace Time
{
    Timer::Timer(IElapsedTimeProvider& elapsedTimeProvider, const long interval)
        : _elapsedTimeProvider(elapsedTimeProvider), _interval(interval)
    {
    }

    bool Timer::HasIntervalElapsed()
    {
        _timeNow = _elapsedTimeProvider.ElapsedMilliseconds();
        if (_timeNow - _timeLastRun > _interval) 
        {
            _timeLastRun = static_cast<unsigned long>(_timeNow / _interval) * _interval;
            return true;
        }

        return false;
    }

    void Timer::Reset()
    {
        _timeLastRun = _elapsedTimeProvider.ElapsedMilliseconds();
    }

    void Timer::SetInterval(const long interval)
    {
        _interval = interval;
    }


}
