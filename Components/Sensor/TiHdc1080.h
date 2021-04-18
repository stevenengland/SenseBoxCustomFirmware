#pragma once

#include "ISensor.h"
#include "ITiHdc1080Driver.h"

namespace Sensor
{
    class TiHdc1080 final : public ISensor
    {
    public:
        explicit TiHdc1080(ITiHdc1080Driver& driver)
            : _driver(driver)
        {
        }

        bool Init() override;
        float ReadValue(int phenomenonId = 0) override;
        SensorReads ReadValues() override;
    private:
        ITiHdc1080Driver& _driver;        
    };
}
