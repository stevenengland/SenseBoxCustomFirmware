#include "TiHdc1080Humidity.h"

namespace Sensor
{
    bool TiHdc1080Humidity::Init()
    {
        _driver.Begin();
        return true;
    }

    float TiHdc1080Humidity::ReadValue()
    {
        return _driver.ReadHumidity();
    }
}
