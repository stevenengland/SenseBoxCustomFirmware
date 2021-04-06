#include "Measurement.h"
#include "MeasurementContainer.h"

namespace Measurement
{
    void MeasurementContainer::AddMeasurement(Measurement& measurement)
    {
        if (_measurements.size() < _capacity)
        {
            _measurements.push_back(measurement);
        }
    }

    void MeasurementContainer::ClearMeasurements()
    {
        _measurements.clear();
    }

    bool MeasurementContainer::GetMeasurement(int index, Measurement& measurement)
    {
        if (_measurements.empty() || index < 0 || static_cast<int>(_measurements.size()) < index)
        {
            return false;
        }

        measurement = _measurements[index];
        return true;
    }

    int MeasurementContainer::Count()
    {
        auto size = _measurements.size();
        return static_cast<int>(size); // Could overflow if size is gt INT_MAX.
    }

}
