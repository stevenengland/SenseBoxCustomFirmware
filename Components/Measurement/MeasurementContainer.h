#pragma once

#include <vector>
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
        }

        void AddMeasurement(Measurement& measurement) override;
        void ClearMeasurements() override;
        bool GetMeasurement(int index, Measurement& measurement) override;
        int Count() override;

    private:
        std::vector<Measurement> _measurements{};
        size_t _capacity;
    };
}
