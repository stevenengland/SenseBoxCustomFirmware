#include "MeasurementManager.h"

namespace Measurement
{
    void MeasurementManager::Record(const float value, const time_t measurementTime)
    {
        if (_intervalStart == 0)
        {
            _intervalStart = measurementTime;
        }

        if (measurementTime - _intervalStart >= _intervalDuration)
        {
            // Interval elapsed
            Measurement measurement{ _sensorId, _intervalAggregate, _intervalStart };
            _container.AddMeasurement(measurement);

            _intervalStart = measurementTime;

            _aggregationStrategy.Reset();
        }

        _intervalAggregate = _aggregationStrategy.Aggregate(value);
    }

    void MeasurementManager::SetInterval(const time_t interval)
    {
        _intervalDuration = interval;
    }

}
