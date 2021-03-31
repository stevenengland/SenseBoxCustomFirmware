#include "Arduino.h"
#include "ArduinoElapsedTimeProvider.h"

namespace Time
{
    unsigned long ArduinoElapsedTimeProvider::ElapsedMilliseconds()
    {
        return millis();
    }

    void ArduinoElapsedTimeProvider::WaitSync(int milliseconds)
    {
        delay(milliseconds);
    }

}