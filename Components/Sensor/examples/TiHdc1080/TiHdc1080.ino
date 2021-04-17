#include "Arduino.h"
#include "TiHdc1080Driver.h"
#include "TiHdc1080Temperature.h"
#include "TiHdc1080Humidity.h"

Sensor::TiHdc1080Driver Driver;
Sensor::TiHdc1080Temperature Temperature{ Driver };
Sensor::TiHdc1080Humidity Humidity{ Driver };

// ReSharper disable once CppInconsistentNaming
void setup()
{
    Serial.begin(9600);
    Temperature.Init();
    Humidity.Init();
}

// ReSharper disable once CppInconsistentNaming
void loop()
{
    Serial.print("T: ");
    Serial.println(Temperature.ReadValue());
    Serial.print("H: ");
    Serial.println(Humidity.ReadValue());
    delay(5000);
}
