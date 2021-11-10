#include "Arduino.h"
#include "NovaSds011Driver.h"
#include "NovaSds011.h"

Sensor::NovaSds011Driver Driver{ Serial2 };
Sensor::NovaSds011 Sds{ Driver };

// ReSharper disable once CppInconsistentNaming
void setup()
{
    Serial.begin(9600);
    while(!Serial); // wait for serial monitor
    Serial.println("Init");
    Sds.Init();
    delay(5000);
}

// ReSharper disable once CppInconsistentNaming
void loop()
{
    Serial.print("Loop");
    auto values = Sds.ReadValues();
    Serial.print("25: ");
    Serial.println(values.Reads[0]);
    Serial.print("10: ");
    Serial.println(values.Reads[1]);
    delay(10000);
    Serial.println("Sending sensor to sleep mode. Can you hear it anymore? :)");
    Sds.Sleep();
    delay(10000);
    Serial.println("Trying to read values from the sensor...");
    values = Sds.ReadValues();
    Serial.print("25: ");
    Serial.println(values.Reads[0]);
    Serial.print("10: ");
    Serial.println(values.Reads[1]);
    delay(2000);
    Serial.println("Waking up the sensor again...");
    Sds.Wakeup();
    delay(10000);
    Serial.println("Trying to read values from the sensor...");
    values = Sds.ReadValues();
    Serial.print("25: ");
    Serial.println(values.Reads[0]);
    Serial.print("10: ");
    Serial.println(values.Reads[1]);
    Serial.println("Finished.");
    delay(60000);
}
