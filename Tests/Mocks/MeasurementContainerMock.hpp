#pragma once

#include "IMeasurementContainer.h"
#include "Measurement.h"

namespace Measurement
{
    class MeasurementContainerMock final : public IMeasurementContainer
    {
    public:
        MOCK_METHOD(void, AddMeasurement, (Measurement& measurement), (override));
        MOCK_METHOD(void, ClearMeasurements, (), (override));
        MOCK_METHOD(bool, GetMeasurement, (int index, Measurement &measurement), (override));
        MOCK_METHOD(int, Count, (), (override));
    };
}
