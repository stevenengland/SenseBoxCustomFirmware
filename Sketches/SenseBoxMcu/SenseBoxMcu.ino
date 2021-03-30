#include "Arduino.h"

#include "Timer.h"
#include "ArduinoElapsedTimeProvider.h"

Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Time::Timer SoundLevelMeasurementTimer{ ElapsedTimeProvider, 300 };
Time::Timer GeneralMeasurementTimer{ ElapsedTimeProvider, 60000 };
Time::Timer UploadToOsemTimer{ ElapsedTimeProvider, 300000 };

// ReSharper disable once CppInconsistentNaming
void setup() {
    
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    if(SoundLevelMeasurementTimer.HasIntervalElapsed())
    {
        // Measure Sound Level
    }

    if(GeneralMeasurementTimer.HasIntervalElapsed())
    {
        // Measure all other sensors
    }

    if(UploadToOsemTimer.HasIntervalElapsed())
    {
        // Upload to OSeM
    }
}