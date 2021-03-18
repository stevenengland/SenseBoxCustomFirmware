#include "DfRobotSen0232.h"
#include "SenseBoxAnalogPortReader.h"
#include "Arduino.h"

const int SoundSensorPin = A1;  // This pin reads the analog voltage from the sound level meter

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Connectivity::AnalogPorts::SenseBoxAnalogPortReader analogPortReader;
    SoundLevelMeter::DfRobotSen0232 slm{analogPortReader, SoundSensorPin};
    const auto dbValue = slm.ReadValue();
    Serial.print(dbValue, 1);
    Serial.println(" dBA");
    delay(125);
}
