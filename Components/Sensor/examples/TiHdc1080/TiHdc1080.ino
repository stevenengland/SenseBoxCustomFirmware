#include "Arduino.h"
#include "TiHdc1080Driver.h"
#include "TiHdc1080.h"

Sensor::TiHdc1080Driver Driver;
Sensor::TiHdc1080 TiHdc1080{ Driver };

// ReSharper disable once CppInconsistentNaming
void setup()
{
    Serial.begin(9600);
    TiHdc1080.Init();
}

// ReSharper disable once CppInconsistentNaming
void loop()
{
    const auto values = TiHdc1080.ReadValues();
    Serial.print("T: ");
    Serial.println(values.Reads[0]);
    Serial.print("H: ");
    Serial.println(values.Reads[1]);
    delay(5000);
}
