#include "SenseboxMcuSketchCoupling.h"

namespace Sketch
{
    void SenseboxMcuSketchCoupling::Setup()
    {
        
    }

    void SenseboxMcuSketchCoupling::Loop()
    {
        // Check timers
        if (_soundLevelMeasurementTimer.HasIntervalElapsed())
        {
            // Measure Sound Level
            _soundLevelMeter.ReadValue();
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
}
