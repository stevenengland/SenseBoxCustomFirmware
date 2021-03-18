#pragma once

#include "AnalogPortReader.h"
#include "SoundLevelMeter.h"

namespace SoundLevelMeter
{
    class DfRobotSen0232 final : public SoundLevelMeter
    {
    public:
        explicit DfRobotSen0232(
            Connectivity::AnalogPorts::AnalogPortReader& portReader,
            int soundSensorPin
        );

        float ReadValue() override;

    private:
        Connectivity::AnalogPorts::AnalogPortReader& _portReader;
        int _soundSensorPin;
    };
}
