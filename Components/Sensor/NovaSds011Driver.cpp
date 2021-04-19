#include "NovaSds011Driver.h"

#include <cstdint>

namespace Sensor
{
    void NovaSds011Driver::Begin()
    {
        if (!_needsInit)
        {
            return;
        }
        _uart.begin(9600);
        _needsInit = false;
    }

    void NovaSds011Driver::Read(float& p25, float& p10, bool& error)
    {
        uint8_t attempt = 0;
        float pm10, pm25;
        while (attempt < 5) {
            error = _sds.read(&pm25, &pm10);
            if (!error) {
                p25 = pm25;
                p10 = pm10;
                break;
            }
            attempt++;
        }
    }
}
