#pragma once

#include "IAnalogPortReader.h"
#include "SoundLevelMeter.h"

namespace SoundLevelMeter
{
    class DfRobotSen0232 final : public SoundLevelMeter
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
