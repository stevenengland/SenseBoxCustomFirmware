#include "Arduino.h"
#include "ArduinoWatchDog.h"
#include "ArduinoElapsedTimeProvider.h"
#include "DfRobotSen0232.h"
#include "MeasurementContainer.h"
#include "SenseBoxAnalogPortReader.h"
#include "SenseboxMcuSketchCoupling.h"

// Prepare IoC
Time::ArduinoWatchDog WatchDog;
Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Peripherals::SenseBoxAnalogPortReader AnalogPortReader;
SoundLevelMeter::DfRobotSen0232 SlMeter{AnalogPortReader, A1};
Measurement::MeasurementContainer MeasurementContainer{1000};
Sketch::SenseboxMcuSketchCoupling SketchCoupling
{
    WatchDog,
    ElapsedTimeProvider,
    SlMeter,
    MeasurementContainer
};

// ReSharper disable once CppInconsistentNaming
void setup() {
    SketchCoupling.Setup();
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    SketchCoupling.Loop();
}