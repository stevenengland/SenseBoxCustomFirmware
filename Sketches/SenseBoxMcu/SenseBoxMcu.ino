#include "Arduino.h"
#include "ArduinoWatchDog.h"
#include "ArduinoElapsedTimeProvider.h"
#include "SenseboxMcuSketchCoupling.h"

// Prepare IoC
Time::ArduinoWatchDog WatchDog;
Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Sketch::SenseboxMcuSketchCoupling SketchCoupling
{
    WatchDog,
    ElapsedTimeProvider
};

// ReSharper disable once CppInconsistentNaming
void setup() {
    SketchCoupling.Setup();
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    SketchCoupling.Loop();
}