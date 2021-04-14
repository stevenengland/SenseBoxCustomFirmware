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
#include "WifiManager.h"
#include "Winc1500WifiConnector.h"
#include "LogLevel.h"
#include "RamInfoReader.h"
#include "SerialLogger.h"

// Reading config
const char Ssid[] = SECRET_SSID;
const char Pass[] = SECRET_PASS;
const char SlmId[] PROGMEM = SECRET_SENSOR_SOUND_ID;

// Prepare Config
Sketch::SketchConfiguration Configuration = []
{
    Sketch::SketchConfiguration c{};

    c.Logger_LogLevel = LogLevelVerbose;
    c.TimeProvider_TimeRequest_RetryInterval = 1000;
    c.TimeProvider_TimeRequest_RetryCount = 5;
    c.NetworkProvider_ConnectionRequest_RetryInterval = 1000;
    c.NetworkProvider_ConnectionRequest_RetryCount = 20;
    c.NetworkProvider_ConnectionStatus_CheckInterval = 30000;
    c.WatchDog_KeepAlive_TimeoutInterval = 16000;
    c.MeasurementContainer_Capacity = 1000;
    c.Sensor_Measure_Interval = 60000;
    c.SoundLevelMeter_Measure_Interval = 300;
    c.SoundLevelMeter_Measure_AggregationInterval = 1;
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
Measurement::MeasurementContainer MeasurementContainer{Configuration.MeasurementContainer_Capacity};
Measurement::MeasurementManager SlmMeasurementManager
{
    MeasurementContainer,
    AggregationStrategy,
    Configuration.SoundLevelMeter_Measure_AggregationInterval,
    SlmId
};
Network::Wifi::Winc1500WifiConnector WifiConnector;
Network::Wifi::WifiManager WifiManager{ WifiConnector, Ssid, Pass };
CentralUnit::RamInfoReader RamInfoReader;
Logging::SerialLogger Logger{Configuration.Logger_LogLevel};
Sketch::SenseboxMcuSketchCoupling SketchCoupling
{
    SenseBoxIoMapper,
    WatchDog,
    ElapsedTimeProvider,
    TimeProvider,
    SlMeter,
    MeasurementContainer,
    SlmMeasurementManager,
    WifiManager,
    RamInfoReader,
    Logger,
    Configuration
};

// ReSharper disable once CppInconsistentNaming
void setup() {
    Serial.begin(115200);
    SketchCoupling.Setup();
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    SketchCoupling.Loop();
}