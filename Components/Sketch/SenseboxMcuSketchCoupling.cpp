#include "SenseboxMcuSketchCoupling.h"

namespace Sketch
{
    void SenseboxMcuSketchCoupling::Setup()
    {
        _logger.Notice("Starting device\n");

        // Disable WatchDog until setup is done.
        _watchDog.Disable();

        // Wait a little so that serial can be plugged in
        _elapsedTimeProvider.WaitSync(5000);

        _logger.Notice("Starting services\n");

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

        _logger.Notice("Device successfully started\n");

        HealthCheck();
    }

    void SenseboxMcuSketchCoupling::Loop()
    {
        // Check timers
        if (_soundLevelMeasurementTimer.HasIntervalElapsed())
        {
            // Measure Sound Level
            _slmMeasurementManager.Record(_soundLevelMeter.ReadValue(), _timeProvider.GetEpochTime());
        }

        if (_generalMeasurementTimer.HasIntervalElapsed())
        {
            // Measure all other sensors
        }

        if(_checkAndReconnectWifiTimer.HasIntervalElapsed())
        {
            // Periodic check for a WiFi connection
            if (!_wifiManager.IsConnected())
            {
                _wifiManager.Reconnect();
            }
        }

        if (_uploadToOsemTimer.HasIntervalElapsed())
        {
            // Upload to OSeM

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
            auto currentTime = _timeProvider.GetEpochTime();
            if (currentTime > 0)
            {
                _logger.Notice("Time Provider detected current timestamp: %d\n", currentTime);

                return true;
            }

            _elapsedTimeProvider.WaitSync(_configuration.TimeProvider_TimeRequest_RetryInterval);
            _watchDog.Reset();
        }

        _logger.Error("Time Provider was not able to provide a valid time\n");

        return false;
    }

    bool SenseboxMcuSketchCoupling::CheckWifiConnection(const int retryCounter) const
    {
        for (auto i = 1; i <= retryCounter; i++)
        {
            if (_wifiManager.IsConnected())
            {
                _logger.Notice("Network Provider successfully connected to network\n");

                return true;
            }

            _elapsedTimeProvider.WaitSync(_configuration.NetworkProvider_ConnectionRequest_RetryInterval);
            _watchDog.Reset();
        }

        _logger.Error("Network Provider was not able to connect to network\n");

        return false;
    }

    void SenseboxMcuSketchCoupling::Reset() const
    {
        _logger.Fatal("Resetting device\n");
        _elapsedTimeProvider.WaitSync(_watchDogInterval * 2);
    }

    void SenseboxMcuSketchCoupling::HealthCheck() const
    {
        _logger.Notice("> --- Health check: ---\n");
        _logger.Notice("> Current timestamp: %d\n", _timeProvider.GetEpochTime());
        _logger.Notice("> Network connected: %d\n", (_wifiManager.IsConnected() ? 1 : 0));
        _logger.Notice("> Measurement container fill level: %d\n", _measurementContainer.Count());
        _logger.Notice("> Free SRAM: %d\n", _ramInfoReader.GetFreeRamSize());
    }
}
