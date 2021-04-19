#pragma once

#include "ISensor.h"
#include "INovaSds011Driver.h"

namespace Sensor
{
    class NovaSds011 final : public ISensor
    {
    public:
        explicit NovaSds011(INovaSds011Driver& driver)
            : _driver(driver)
        {

        }
        float ReadValue(int phenomenonId = 0) override;
        SensorReads ReadValues() override;
        bool Init() override;
    private:
        INovaSds011Driver& _driver;
    };
}
