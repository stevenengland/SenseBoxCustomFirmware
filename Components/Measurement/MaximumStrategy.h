#pragma once

#include "IMeasurementAggregationStrategy.h"

namespace Measurement
{
    class MaximumStrategy final : public IMeasurementAggregationStrategy
    {
    public:
        float Aggregate(float currentAggregate, float nextValue) override;
    };
}
