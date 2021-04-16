#pragma once

#include <gmock/gmock.h>

#include "../../Components/Measurement/IMeasurementAggregationStrategy.h"

namespace Measurement
{
    class MeasurementAggregationStrategyMock final : public IMeasurementAggregationStrategy
    {
    public:
        MOCK_METHOD(float, Aggregate, (float nextValue), (override));
        MOCK_METHOD(void, Reset, (), (override));
    };
}
