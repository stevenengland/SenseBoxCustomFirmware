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
            char timeBuffer[21]{};
            _timeConverter.GetUtcTime(_intervalStart, timeBuffer);
            Measurement measurement{ _sensorId, _intervalAggregate, timeBuffer };
            _container.AddMeasurement(measurement);

            _intervalStart = measurementTime;
        }

        _intervalAggregate = _aggregationStrategy.Aggregate(_intervalAggregate, value);
    }

    void MeasurementManager::SetInterval(time_t interval)
    {
        _intervalDuration = interval;
    }

}
