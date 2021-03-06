#include "DfRobotSen0232.h"
#include "SenseBoxAnalogPortReader.h"
#include "Arduino.h"
#include "senseBoxIO.h"

const int SoundSensorPin = A1;  // This pin reads the analog voltage from the sound level meter
Peripherals::SenseBoxAnalogPortReader analogPortReader;
Sensor::DfRobotSen0232 slm{analogPortReader, SoundSensorPin};

void setup()
{
    senseBoxIO.powerAll();
    Serial.begin(115200);
}

void loop()
{
    const auto dbValue = slm.ReadValue();
    Serial.print(dbValue, 1);
    Serial.println(" dBA");
    delay(125);
}
