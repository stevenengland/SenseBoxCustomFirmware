#pragma once

#include "IAnalogPortReader.h"
#include "ISensor.h"

namespace Sensor
{
    class DfRobotSen0232 final : public ISensor
    {
    public:
        explicit DfRobotSen0232(
            Peripherals::IAnalogPortReader& portReader,
            int soundSensorPin
        );

        float ReadValue() override;

    private:
        Peripherals::IAnalogPortReader& _portReader;
        int _soundSensorPin;
    };
}
