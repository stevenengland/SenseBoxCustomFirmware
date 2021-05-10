#include "Arduino.h"
#include "ArduinoElapsedTimeProvider.h"
#include "ArduinoWatchDog.h"
#include "arduino_secrets.h"
#include "DfRobotSen0232.h"
#include "HttpTerminal.h"
#include "LogLevel.h"
#include "MaximumStrategy.h"
#include "MeasurementContainer.h"
#include "MeasurementRecorder.h"
#include "MeasurementToCsvLineConverter.h"
#include "MeasurementToOsemUploader.h"
#include "NovaSds011.h"
#include "NovaSds011Driver.h"
#include "RamInfoReader.h"
#include "SenseBoxAnalogPortReader.h"
#include "SenseboxMcuSketchCoupling.h"
#include "SerialLogger.h"
#include "TcpStream.h"
#include "TiHdc1080.h"
#include "TiHdc1080Driver.h"
#include "TimeConverter.h"
#include "WifiManager.h"
#include "Winc1500TelnetLogger.h"
#include "Winc1500TimeProvider.h"
#include "Winc1500WifiConnector.h"

// Reading config
const char Ssid[] = SECRET_SSID;
const char Pass[] = SECRET_PASS;
const char BoxId[] PROGMEM = BOX_ID;
const char AuthToken[] PROGMEM = AUTH_TOKEN;
const char SlmId[] PROGMEM = SECRET_SENSOR_SOUND_ID; // Sound level meter
const char TempSensorId[] PROGMEM = TEMP_SENSOR_ID; // Temperature
const char RelHumiditySensorId[] PROGMEM = REL_HUMIDITY_SENSOR_ID; // Rel. humidity
const char Pm10SensorId[] PROGMEM = PM10_SENSOR_ID; // PM10
const char Pm25SensorId[] PROGMEM = PM25_SENSOR_ID; // PM2.5

const char ServerHostName[] = "ingress.opensensemap.org";

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
    c.MeasurementContainer_Capacity = 1300;
    c.Sensor_Measure_Interval = 60000;
    c.Sensor_Measure_AggregationInterval = 0;
    c.SoundLevelMeter_Measure_Interval = 300;
    c.SoundLevelMeter_Measure_AggregationInterval = 1;
    c.FineDustSensor_Measure_Interval = 600000;
    c.Osem_Upload_Interval = 300000;
    c.Osem_Upload_Interval_ErrorCondition = 60000;
    c.HealthCheck_Interval = 60000;

    return c;
}();

// Prepare IoC
CentralUnit::RamInfoReader RamInfoReader;
//Logging::SerialLogger Logger{ Configuration.Logger_LogLevel };
Logging::Winc1500TelnetLogger Logger{ Configuration.Logger_LogLevel };
Measurement::MaximumStrategy SlmAggregationStrategy;
Measurement::MaximumStrategy TemperatureAggregationStrategy;
Measurement::MaximumStrategy HumidityAggregationStrategy;
Measurement::MaximumStrategy FineDustP25AggregationStrategy;
Measurement::MaximumStrategy FineDustP10AggregationStrategy;
Measurement::MeasurementContainer MeasurementContainer{ Configuration.MeasurementContainer_Capacity };
Network::Wifi::Winc1500WifiConnector WifiConnector;
Network::TcpStream TcpStream;
Peripherals::SenseBoxIoMapper SenseBoxIoMapper;
Peripherals::SenseBoxAnalogPortReader AnalogPortReader;
Sensor::TiHdc1080Driver TiHdc1080Driver;
Sensor::NovaSds011Driver NovaSds011Driver{ Serial2 };
Sensor::DfRobotSen0232 SlMeter{AnalogPortReader, A1};
Time::ArduinoWatchDog WatchDog;
Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Time::Winc1500TimeProvider TimeProvider;
Time::TimeConverter TimeConverter;

Sensor::TiHdc1080 TemperatureSensor { TiHdc1080Driver };
Sensor::TiHdc1080 HumiditySensor{ TiHdc1080Driver };
Sensor::NovaSds011 NovaSds{ NovaSds011Driver };
Network::Wifi::WifiManager WifiManager{ WifiConnector, Ssid, Pass };
Network::HttpTerminal Terminal{ TcpStream, ElapsedTimeProvider };
Measurement::MeasurementToCsvLineConverter Converter{ TimeConverter };
Measurement::MeasurementRecorder SlmMeasurementRecorder
{
    MeasurementContainer,
    SlmAggregationStrategy,
    Configuration.SoundLevelMeter_Measure_AggregationInterval,
    SlmId
};
Measurement::MeasurementRecorder TemperatureMeasurementRecorder
{
    MeasurementContainer,
    TemperatureAggregationStrategy,
    Configuration.Sensor_Measure_AggregationInterval,
    TempSensorId
};
Measurement::MeasurementRecorder HumidityMeasurementRecorder
{
    MeasurementContainer,
    HumidityAggregationStrategy,
    Configuration.Sensor_Measure_AggregationInterval,
    RelHumiditySensorId
};
Measurement::MeasurementRecorder FineDustP25MeasurementRecorder
{
    MeasurementContainer,
    FineDustP25AggregationStrategy,
    Configuration.Sensor_Measure_AggregationInterval,
    Pm25SensorId
};
Measurement::MeasurementRecorder FineDustP10MeasurementRecorder
{
    MeasurementContainer,
    FineDustP10AggregationStrategy,
    Configuration.Sensor_Measure_AggregationInterval,
    Pm10SensorId
};
Measurement::MeasurementToOsemUploader Uploader
{
    Terminal,
    Converter,
    ServerHostName,
    443,
    BoxId,
    AuthToken
};

Sketch::SenseboxMcuSketchCoupling SketchCoupling
{
    SenseBoxIoMapper,
    WatchDog,
    ElapsedTimeProvider,
    TimeProvider,
    SlMeter,
    TemperatureSensor,
    HumiditySensor,
    NovaSds,
    MeasurementContainer,
    SlmMeasurementRecorder,
    TemperatureMeasurementRecorder,
    HumidityMeasurementRecorder,
    FineDustP25MeasurementRecorder,
    FineDustP10MeasurementRecorder,
    Uploader,
    WifiManager,
    RamInfoReader,
    Logger,
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