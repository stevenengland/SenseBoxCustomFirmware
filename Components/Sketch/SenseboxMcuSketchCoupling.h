#pragma once

#include "ISketchCoupling.h"
#include "IWatchDog.h"
#include "Timer.h"
#include "IElapsedTimeProvider.h"
#include "IMeasurementContainer.h"
#include "ISensor.h"
#include "IMeasurementManager.h"
#include "ITimeProvider.h"
#include "IWifiManager.h"
#include "SenseBoxIoMapper.h"
#include "SketchConfiguration.h"
#include "IRamInfoReader.h"
#include "ILogger.h"

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
            Measurement::IMeasurementContainer& measurementContainer,
            Measurement::IMeasurementManager& slmMeasurementManager,
            Network::Wifi::IWifiManager& wifiManager,
            CentralUnit::IRamInfoReader& ramInfoReader,
            Logging::ILogger& logger,
            SketchConfiguration& configuration)
            : _senseBoxIoMapper(senseBoxIoMapper),
              _watchDog(watchDog),
              _elapsedTimeProvider(elapsedTimeProvider),
              _timeProvider(timeProvider),
              _soundLevelMeter(soundLevelMeter),
              _measurementContainer(measurementContainer),
              _slmMeasurementManager(slmMeasurementManager),
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
        Measurement::IMeasurementContainer& _measurementContainer;
        Measurement::IMeasurementManager& _slmMeasurementManager;
        Network::Wifi::IWifiManager& _wifiManager;
        CentralUnit::IRamInfoReader& _ramInfoReader;
        Logging::ILogger& _logger;
        SketchConfiguration& _configuration;
        Time::Timer _soundLevelMeasurementTimer{ _elapsedTimeProvider, _configuration.SoundLevelMeter_Measure_Interval };
        Time::Timer _generalMeasurementTimer{ _elapsedTimeProvider, _configuration.Sensor_Measure_Interval };
        Time::Timer _uploadToOsemTimer{ _elapsedTimeProvider, _configuration.Osem_Upload_Interval };
        Time::Timer _checkAndReconnectWifiTimer{ _elapsedTimeProvider, _configuration.NetworkProvider_ConnectionStatus_CheckInterval };
        Time::Timer _healthCheckTimer{ _elapsedTimeProvider, _configuration.HealthCheck_Interval };
        //Time::Timer _soundLevelMeasurementTimer;
        //Time::Timer _generalMeasurementTimer;
        //Time::Timer _uploadToOsemTimer;

        int _watchDogInterval = _configuration.WatchDog_KeepAlive_TimeoutInterval;

        bool CheckTimeProvider(int retryCounter) const;
        bool CheckWifiConnection(int retryCounter) const;
        void Reset() const;
        void HealthCheck() const;
    };
}
