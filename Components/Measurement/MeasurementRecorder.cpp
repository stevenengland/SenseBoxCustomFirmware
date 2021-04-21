#include "MeasurementRecorder.h"

namespace Measurement
{
    void MeasurementRecorder::Record(const float value, const time_t measurementTime)
    {
        if (_intervalStart == 0)
        {
            _intervalStart = measurementTime;
        }

        if (_intervalDuration == 0) // Every record should create a measurement, so build the aggregate anyway.
        {
            _intervalAggregate = _aggregationStrategy.Aggregate(value);
        }

        if (measurementTime - _intervalStart >= _intervalDuration)
        {
            // Interval elapsed
            Measurement measurement{ _sensorId, _intervalAggregate, _intervalStart };
            _container.AddMeasurement(measurement);

            _intervalStart = measurementTime;

            _aggregationStrategy.Reset();
        }

        if (_intervalDuration > 0) // If not every record should create a measurement now is the time to build the aggregate.
        {
            _intervalAggregate = _aggregationStrategy.Aggregate(value);
        }
    }

    void MeasurementRecorder::SetInterval(const time_t interval)
    {
        _intervalDuration = interval;
    }

}
