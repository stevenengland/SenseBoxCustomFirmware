#pragma once

#include "ISketchCoupling.h"
#include "IWatchDog.h"
#include "Timer.h"
#include "IElapsedTimeProvider.h"
#include "IMeasurementContainer.h"
#include "ISensor.h"
#include "IHibernatableSensor.h"
#include "IMeasurementRecorder.h"
#include "ITimeProvider.h"
#include "IWifiManager.h"
#include "SenseBoxIoMapper.h"
#include "SketchConfiguration.h"
#include "IRamInfoReader.h"
#include "ILogger.h"
#include "IMeasurmentUploader.h"

namespace Sketch
{
    class SenseboxMcuSketchCoupling final : public ISketchCoupling
    {
    public:
        SenseboxMcuSketchCoupling(
            Peripherals::ISenseBoxIoMapper& senseBoxIoMapper,
            Time::IWatchDog& watchDog,
            Time::IElapsedTimeProvider& elapsedTimeProvider,
            Time::ITimeProvider& timeProvider,
            Sensor::ISensor& soundLevelMeter,
            Sensor::ISensor& temperatureSensor,
            Sensor::ISensor& humiditySensor,
            Sensor::IHibernatableSensor& fineDustSensor,
            Measurement::IMeasurementContainer& measurementContainer,
            Measurement::IMeasurementRecorder& slmMeasurementRecorder,
            Measurement::IMeasurementRecorder& temperatureMeasurementRecorder,
            Measurement::IMeasurementRecorder& humidityMeasurementRecorder,
            Measurement::IMeasurementRecorder& fineDustP25MeasurementRecorder,
            Measurement::IMeasurementRecorder& fineDustP10MeasurementRecorder,
            Measurement::IMeasurementUploader& measurementUploader,
            Network::Wifi::IWifiManager& wifiManager,
            CentralUnit::IRamInfoReader& ramInfoReader,
            Logging::ILogger& logger,
            SketchConfiguration& configuration)
            : _senseBoxIoMapper(senseBoxIoMapper),
              _watchDog(watchDog),
              _elapsedTimeProvider(elapsedTimeProvider),
              _timeProvider(timeProvider),
              _soundLevelMeter(soundLevelMeter),
              _temperatureSensor(temperatureSensor),
              _humiditySensor(humiditySensor),
              _fineDustSensor(fineDustSensor),
              _measurementContainer(measurementContainer),
              _slmMeasurementRecorder(slmMeasurementRecorder),
              _temperatureMeasurementRecorder(temperatureMeasurementRecorder),
              _humidityMeasurementRecorder(humidityMeasurementRecorder),
              _fineDustP25MeasurementRecorder(fineDustP25MeasurementRecorder),
              _fineDustP10MeasurementRecorder(fineDustP10MeasurementRecorder),
              _measurementUploader(measurementUploader),
              _wifiManager(wifiManager),
              _ramInfoReader(ramInfoReader),
              _logger(logger),
              _configuration(configuration)
        // _soundLevelMeasurementTimer(_elapsedTimeProvider, 300),
        //_generalMeasurementTimer(_elapsedTimeProvider, 60000),
        //_uploadToOsemTimer(_elapsedTimeProvider, 300000)
        {
        }

        void Setup() override;
        void Loop() override;
    private:
        Peripherals::ISenseBoxIoMapper& _senseBoxIoMapper;
        Time::IWatchDog& _watchDog;
        Time::IElapsedTimeProvider& _elapsedTimeProvider;
        Time::ITimeProvider& _timeProvider;
        Sensor::ISensor& _soundLevelMeter;
        Sensor::ISensor& _temperatureSensor;
        Sensor::ISensor& _humiditySensor;
        Sensor::IHibernatableSensor& _fineDustSensor;
        Measurement::IMeasurementContainer& _measurementContainer;
        Measurement::IMeasurementRecorder& _slmMeasurementRecorder;
        Measurement::IMeasurementRecorder& _temperatureMeasurementRecorder;
        Measurement::IMeasurementRecorder& _humidityMeasurementRecorder;
        Measurement::IMeasurementRecorder& _fineDustP25MeasurementRecorder;
        Measurement::IMeasurementRecorder& _fineDustP10MeasurementRecorder;
        Measurement::IMeasurementUploader& _measurementUploader;
        Network::Wifi::IWifiManager& _wifiManager;
        CentralUnit::IRamInfoReader& _ramInfoReader;
        Logging::ILogger& _logger;
        SketchConfiguration& _configuration;
        Time::Timer _soundLevelMeasurementTimer{ _elapsedTimeProvider, _configuration.SoundLevelMeter_Measure_Interval };
        Time::Timer _fineDustSensorMeasurementTimer{ _elapsedTimeProvider, _configuration.FineDustSensor_Measure_Interval };
        Time::Timer _fineDustSensorWakeupTimer{ _elapsedTimeProvider, _configuration.FineDustSensor_Measure_Interval - 60000 };
        Time::Timer _generalMeasurementTimer{ _elapsedTimeProvider, _configuration.Sensor_Measure_Interval };
        Time::Timer _uploadToOsemTimer{ _elapsedTimeProvider, _configuration.Osem_Upload_Interval };
        Time::Timer _checkAndReconnectWifiTimer{ _elapsedTimeProvider, _configuration.NetworkProvider_ConnectionStatus_CheckInterval };
        Time::Timer _healthCheckTimer{ _elapsedTimeProvider, _configuration.HealthCheck_Interval };
        //Time::Timer _soundLevelMeasurementTimer;
        //Time::Timer _generalMeasurementTimer;
        //Time::Timer _uploadToOsemTimer;

        int _watchDogInterval = _configuration.WatchDog_KeepAlive_TimeoutInterval;

        int _lastKnownContainerFillCount = 0;

        bool CheckTimeProvider(int retryCounter) const;
        bool CheckWifiConnection(int retryCounter) const;
        void Reset() const;
        void HealthCheck() const;
        void LogContainerDelta();
    };
}
