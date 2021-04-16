#include "Measurement.h"
#include "MeasurementContainer.h"

namespace Measurement
{
    void MeasurementContainer::AddMeasurement(Measurement& measurement)
    {
        if (_currentItemIndex < _capacity)
        {
            _measurements[_currentItemIndex] = measurement;
            _currentItemIndex++;
        }
    }

    void MeasurementContainer::ClearMeasurements()
    {
        _currentItemIndex = 0;
    }

    bool MeasurementContainer::GetMeasurement(const int index, Measurement& measurement)
    {
        if (_currentItemIndex == 0 || index < 0 || static_cast<int>(_currentItemIndex - 1) < index)
        {
            return false;
        }

        measurement = _measurements[index];
        return true;
    }

    int MeasurementContainer::Count()
    {
        return static_cast<int>(_currentItemIndex); // Could overflow if size is gt INT_MAX.
    }

}
