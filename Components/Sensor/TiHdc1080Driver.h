#pragma once

#include "ITiHdc1080Driver.h"
#include <Adafruit_HDC1000.h>

namespace Sensor
{
    class TiHdc1080Driver final : public ITiHdc1080Driver
    {
    public:
        void Begin() override;
        float ReadTemperature() override;
        float ReadHumidity() override;
    private:
        bool _needsInit = true;
        Adafruit_HDC1000 _hdc = Adafruit_HDC1000();
    };
}
