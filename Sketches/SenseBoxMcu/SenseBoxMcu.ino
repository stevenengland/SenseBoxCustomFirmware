#include "Arduino.h"

const long SlmMeasurementInterval = 300;
long SlmMeasurementTimeStart = 0;
long SlmMeasurementTimeActual = 0;

//const long SlmInterval = 300;
//long SlmTimeStart = 0;
//long SlmTimeActual = 0;

bool HasSlmMeasurementTimeCome()
{
    SlmMeasurementTimeStart = millis();
    if (SlmMeasurementTimeStart > SlmMeasurementTimeActual + SlmMeasurementInterval) {
        SlmMeasurementTimeActual = millis();
        return true;
    }

    return false;
}

// ReSharper disable once CppInconsistentNaming
void setup() {
    
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    if (HasSlmMeasurementTimeCome())
    {
        
    }
}