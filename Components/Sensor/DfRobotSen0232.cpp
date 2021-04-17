#include "DfRobotSen0232.h"

namespace Sensor
{
    DfRobotSen0232::DfRobotSen0232(
        Peripherals::IAnalogPortReader& portReader,
        const int soundSensorPin)
        :
    _portReader{portReader},
    _soundSensorPin(soundSensorPin)
    {
    }

    bool DfRobotSen0232::Init()
    {
        return true;
    }

    float DfRobotSen0232::ReadValue()
    {
        const auto voltage = _portReader.ReadVoltageFromPin(_soundSensorPin) / 1024.0f * 3.3f;
        const auto dbValue = voltage * 50.0f;  //convert voltage to decibel value 
        return dbValue;
    }
}
