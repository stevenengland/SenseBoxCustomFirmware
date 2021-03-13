#include "DfRobotSen0232.h"
#include "ArduinoAnalogPortReader.h"

const int SoundSensorPin = 1;  //this pin read the analog voltage from the sound level meter

void setup()
{
    Serial.begin(115200);
}

void loop()
{
    Arduino::ArduinoAnalogPortReader analogPortReader;
    SoundLevelMeter::DfRobotSen0232 slm{analogPortReader, SoundSensorPin};
    //dbValue = voltageValue * 50.0;  //convert voltage to decibel value
    //Serial.print(dbValue,1);
    Serial.println(" dBA");
    delay(125);
}
