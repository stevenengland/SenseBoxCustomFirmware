#pragma once

#include "INovaSds011Driver.h"
#include "Uart.h"
#include <SDS011-select-serial.h>

namespace Sensor
{
    class NovaSds011Driver final : public INovaSds011Driver
    {
    public:
        explicit NovaSds011Driver(Uart& uart)
            : _uart(uart),
              _sds{uart}
        {
        }

        void Begin() override;
        void Read(float& p25, float& p10, bool& error) override;
        void Sleep() override;
        void Wakeup() override;
    private:
        bool _needsInit = true;
        Uart& _uart;
        SDS011 _sds;
    };
}
