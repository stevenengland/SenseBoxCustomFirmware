#pragma once

#include "ISensor.h"
#include "ITiHdc1080Driver.h"

namespace Sensor
{
    class TiHdc1080Humidity final : public ISensor
    {
    public:
        explicit TiHdc1080Humidity(ITiHdc1080Driver& driver)
            : _driver(driver)
        {
        }

        float ReadValue() override;
        bool Init() override;
    private:
        ITiHdc1080Driver& _driver;
    };
}
