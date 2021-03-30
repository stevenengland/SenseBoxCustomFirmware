#include "ArduinoWatchDog.h"
#include "Adafruit_SleepyDog.h"

namespace Time
{
    int ArduinoWatchDog::Enable(int milliseconds)
    {
        return Watchdog.enable(milliseconds);
    }

    void ArduinoWatchDog::Disable()
    {
        Watchdog.disable();
    }

    void ArduinoWatchDog::Reset()
    {
        Watchdog.reset();   
    }
}
