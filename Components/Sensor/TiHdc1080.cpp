#include "TiHdc1080.h"

#include <math.h>

namespace Sensor
{
    bool TiHdc1080::Init()
    {
        _driver.Begin();
        return true;
    }

    float TiHdc1080::ReadValue(const int phenomenonId)
    {
        switch (phenomenonId)
        {
            case 0:
                return _driver.ReadTemperature();
            case 1:
                return _driver.ReadHumidity();
            default: 
                return NAN;
        }
    }

    SensorReads TiHdc1080::ReadValues()
    {
        SensorReads reads{};
        reads.Reads[0] = _driver.ReadTemperature();
        reads.Reads[1] = _driver.ReadHumidity();
        return reads;
    }
}
