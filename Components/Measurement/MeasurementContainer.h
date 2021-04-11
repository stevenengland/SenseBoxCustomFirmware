#pragma once

#include "IMeasurementContainer.h"

namespace Measurement
{
    class MeasurementContainer final : public IMeasurementContainer
    {
    public:
        MeasurementContainer(size_t capacity)
            :
        _capacity(capacity)
        {
            _measurements = new Measurement[capacity];
        }

        ~MeasurementContainer()
        {
            delete[] _measurements;
        }

        void AddMeasurement(Measurement& measurement) override;
        void ClearMeasurements() override;
        bool GetMeasurement(int index, Measurement& measurement) override;
        int Count() override;

    private:
        Measurement* _measurements = nullptr;
        size_t _capacity;
        size_t _currentItemIndex = 0;
    };
}
