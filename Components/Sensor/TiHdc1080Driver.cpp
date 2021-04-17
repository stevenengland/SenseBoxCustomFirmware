#include "TiHdc1080Driver.h"

namespace Sensor
{
    void TiHdc1080Driver::Begin()
    {
        if (!_needsInit)
        {
            return;
        }

        _hdc.begin();
        _needsInit = false;
    }

    float TiHdc1080Driver::ReadTemperature()
    {
        return _hdc.readTemperature();
    }

    float TiHdc1080Driver::ReadHumidity()
    {
        return _hdc.readHumidity();
    }
}
