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

        bool Init() override;
        float ReadValue(int phenomenonId = 0) override;
        SensorReads ReadValues() override;
    private:
        Peripherals::IAnalogPortReader& _portReader;
        int _soundSensorPin;

        float GetDb() const;
    };
}
