#pragma once

#include "SoundLevelMeter.h"
#include "../Arduino/AnalogPortReader.h"

namespace SoundLevelMeter
{
    class DfRobotSen0232 final : public SoundLevelMeter
    {
    public:
        explicit DfRobotSen0232(
            Arduino::AnalogPortReader& portReader,
            int soundSensorPin
        );

        float ReadValue() override;

    private:
        Arduino::AnalogPortReader& _portReader;
        int _soundSensorPin;
    };
}
