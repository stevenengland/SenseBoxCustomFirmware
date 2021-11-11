#pragma once
#include "ISensor.h"
#include "ISensorPowerSaveMode.h"

namespace Sensor
{
    class IHibernatableSensor : public ISensor, public ISensorPowerSaveMode
    {
    };
}
