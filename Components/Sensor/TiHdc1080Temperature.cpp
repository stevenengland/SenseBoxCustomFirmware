#include "TiHdc1080Temperature.h"

namespace Sensor
{
    bool TiHdc1080Temperature::Init()
    {
        _driver.Begin();
        return true;
    }

    float TiHdc1080Temperature::ReadValue()
    {
        return _driver.ReadTemperature();
    }

}
