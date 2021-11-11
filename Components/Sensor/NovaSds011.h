#pragma once

#include "IHibernatableSensor.h"
#include "ISensor.h"
#include "ISensorPowerSaveMode.h"
#include "INovaSds011Driver.h"

namespace Sensor
{
    class NovaSds011 final : public IHibernatableSensor
    {
    public:
        explicit NovaSds011(INovaSds011Driver& driver)
            : _driver(driver)
        {

        }
        float ReadValue(int phenomenonId = 0) override;
        SensorReads ReadValues() override;
        bool Init() override;
        void Sleep() override;
        void Wakeup() override;
    private:
        INovaSds011Driver& _driver;
    };
}
