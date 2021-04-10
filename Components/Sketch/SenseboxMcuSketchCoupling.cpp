#include "SenseboxMcuSketchCoupling.h"

namespace Sketch
{
    void SenseboxMcuSketchCoupling::Setup()
    {
        // Disable WatchDog until setup is done.
        _watchDog.Disable();

        // Check that the time provider is up and running.
        if (!CheckTimeProvider(20))
        {
            // Reset
        }

        // Finally enable WatchDog
        _watchDog.Enable(16000);
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

        if (_uploadToOsemTimer.HasIntervalElapsed())
        {
            // Upload to OSeM

            _measurementContainer.ClearMeasurements(); // ToDo: Only if upload was successful
        }

        // Watch the dog ;)
        _watchDog.Reset();
    }

    bool SenseboxMcuSketchCoupling::CheckTimeProvider(const int retryCounter) const
    {
        for (auto i = 1; i < retryCounter; ++i)
        {
            if (_timeProvider.GetEpochTime() > 1)
            {
                return true;
            }
        }

        return false;
    }

}
