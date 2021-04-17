#pragma once

namespace Sensor
{
    class ITiHdc1080Driver
    {
    public:
        virtual ~ITiHdc1080Driver() = default;

        virtual void Begin() = 0;
        virtual float ReadTemperature() = 0;
        virtual float ReadHumidity() = 0;
    };
}
