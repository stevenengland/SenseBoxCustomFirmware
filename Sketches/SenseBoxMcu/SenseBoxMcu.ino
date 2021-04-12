#include "Arduino.h"
#include "ArduinoWatchDog.h"
#include "ArduinoElapsedTimeProvider.h"
#include "DfRobotSen0232.h"
#include "MaximumStrategy.h"
#include "MeasurementContainer.h"
#include "MeasurementManager.h"
#include "SenseBoxAnalogPortReader.h"
#include "SenseboxMcuSketchCoupling.h"
#include "Winc1500TimeProvider.h"
#include "arduino_secrets.h"

// Reading config
const char Ssid[] = SECRET_SSID;
const char Pass[] = SECRET_PASS;
const char SlmId[] PROGMEM = SECRET_SENSOR_SOUND_ID;

// Prepare Config
Sketch::SketchConfiguration Configuration = []
{
    Sketch::SketchConfiguration c{};
    
    c.TimeProvider_TimeRequest_RetryInterval = 1000;
    c.TimeProvider_TimeRequest_RetryCount = 5;
    c.WatchDog_KeepAlive_TimeoutInterval = 16000;
    c.Sensor_Measure_Interval = 60000;
    c.SoundLevelMeter_Measure_Interval = 300;
    c.Osem_Upload_Interval = 300000;

    return c;
}();

// Prepare IoC
Peripherals::SenseBoxIoMapper SenseBoxIoMapper;
Time::ArduinoWatchDog WatchDog;
Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Time::Winc1500TimeProvider TimeProvider;
Peripherals::SenseBoxAnalogPortReader AnalogPortReader;
Sensor::DfRobotSen0232 SlMeter{AnalogPortReader, A1};
Measurement::MaximumStrategy AggregationStrategy;
Measurement::MeasurementContainer MeasurementContainer{1000};
Measurement::MeasurementManager SlmMeasurementManager
{
    MeasurementContainer,
    AggregationStrategy,
    1,
    SlmId
};
Sketch::SenseboxMcuSketchCoupling SketchCoupling
{
    SenseBoxIoMapper,
    WatchDog,
    ElapsedTimeProvider,
    TimeProvider,
    SlMeter,
    MeasurementContainer,
    SlmMeasurementManager,
    Configuration
};

// ReSharper disable once CppInconsistentNaming
void setup() {
    SketchCoupling.Setup();
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    SketchCoupling.Loop();
}