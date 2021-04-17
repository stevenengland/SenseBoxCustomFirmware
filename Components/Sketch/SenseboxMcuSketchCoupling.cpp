#include "SenseboxMcuSketchCoupling.h"

namespace Sketch
{
    void SenseboxMcuSketchCoupling::Setup()
    {
        _logger.Begin();

        _logger.NoticeP("Starting device\n");

        // Disable WatchDog until setup is done.
        _watchDog.Disable();

        // Wait a little so that serial can be plugged in
        _elapsedTimeProvider.WaitSync(5000);

        _logger.NoticeP("Starting services\n");

        // Get up all pins
        _senseBoxIoMapper.PowerAll();

        // Attempt to turn on WiFi
        _wifiManager.Connect();

        // Check that the network provider is up and running.
        if (!CheckWifiConnection(_configuration.NetworkProvider_ConnectionRequest_RetryCount))
        {
            Reset();
        }

        // Check that the time provider is up and running.
        if (!CheckTimeProvider(_configuration.TimeProvider_TimeRequest_RetryCount))
        {
            Reset();
        }

        // Finally enable WatchDog
        _watchDog.Enable(_configuration.WatchDog_KeepAlive_TimeoutInterval);

        _logger.NoticeP("Device successfully started\n");

        HealthCheck();
    }

    void SenseboxMcuSketchCoupling::Loop()
    {
        // Check timers
        if (_soundLevelMeasurementTimer.HasIntervalElapsed())
        {
            // Measure Sound Level
            const auto value = _soundLevelMeter.ReadValue();
            const auto timestamp = _timeProvider.GetEpochTime();
            _slmMeasurementRecorder.Record(value, timestamp);

            LogContainerDelta();
        }

        if (_generalMeasurementTimer.HasIntervalElapsed())
        {
            // Measure all other sensors
            // Record here without manager, right away and create masure,emt
            LogContainerDelta();
        }

        if(_checkAndReconnectWifiTimer.HasIntervalElapsed())
        {
            // Periodic check for a WiFi connection
            if (!_wifiManager.IsConnected())
            {
                _logger.NoticeP("Network connection lost, reconnecting\n");

                _wifiManager.Reconnect();
            }
        }

        if (_uploadToOsemTimer.HasIntervalElapsed())
        {
            // Upload to OSeM
            _logger.NoticeP("Starting upload to OSeM\n");

            _measurementContainer.ClearMeasurements(); // ToDo: Only if upload was successful
        }

        if (_healthCheckTimer.HasIntervalElapsed())
        {
            // How is it going, Ardu bro?
            HealthCheck();
        }

        // Watch the dog ;)
        _watchDog.Reset();
    }

    bool SenseboxMcuSketchCoupling::CheckTimeProvider(const int retryCounter) const
    {
        for (auto i = 1; i <= retryCounter; ++i)
        {
            const auto currentTime = _timeProvider.GetEpochTime();
            if (currentTime > 0)
            {
                _logger.NoticeP("Time Provider detected current timestamp: %d\n", currentTime);

                return true;
            }

            _elapsedTimeProvider.WaitSync(_configuration.TimeProvider_TimeRequest_RetryInterval);
            _watchDog.Reset();
        }

        _logger.ErrorP("Time Provider was not able to provide a valid time\n");

        return false;
    }

    bool SenseboxMcuSketchCoupling::CheckWifiConnection(const int retryCounter) const
    {
        for (auto i = 1; i <= retryCounter; i++)
        {
            if (_wifiManager.IsConnected())
            {
                _logger.NoticeP("Network Provider successfully connected to network\n");

                return true;
            }

            _elapsedTimeProvider.WaitSync(_configuration.NetworkProvider_ConnectionRequest_RetryInterval);
            _watchDog.Reset();
        }

        _logger.ErrorP("Network Provider was not able to connect to network\n");

        return false;
    }

    void SenseboxMcuSketchCoupling::Reset() const
    {
        _logger.FatalP("Resetting device\n");
        _elapsedTimeProvider.WaitSync(_watchDogInterval * 2);
    }

    void SenseboxMcuSketchCoupling::HealthCheck() const
    {
        _logger.Begin();
        _logger.NoticeP("> --- Health check: ---\n");
        _logger.NoticeP("> Current timestamp: %d\n", _timeProvider.GetEpochTime());
        _logger.NoticeP("> Network connected: %d\n", (_wifiManager.IsConnected() ? 1 : 0));
        _logger.NoticeP("> Measurement container fill level: %d\n", _measurementContainer.Count());
        _logger.NoticeP("> Free SRAM: %d\n", _ramInfoReader.GetFreeRamSize());
    }

    void SenseboxMcuSketchCoupling::LogContainerDelta()
    {
        const auto currentContainerFillCount = _measurementContainer.Count();
        if (currentContainerFillCount < _lastKnownContainerFillCount)
        {
            _lastKnownContainerFillCount = 0;
        }

        if (currentContainerFillCount > _lastKnownContainerFillCount)
        {
            _lastKnownContainerFillCount = currentContainerFillCount;
            Measurement::Measurement measurement;
            if (_measurementContainer.GetMeasurement(currentContainerFillCount - 1, measurement))
            {
                const auto castValue = static_cast<int>(measurement.Value * 100);
                _logger.NoticeP("Add measurement #%d: ", currentContainerFillCount);
                _logger.Notice("SID:%s ", measurement.SensorId);
                _logger.Notice("TS:%d ", measurement.Timestamp);
                _logger.Notice("V:%d\n", castValue);
            }
        }
    }
}
