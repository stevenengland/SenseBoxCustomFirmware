#pragma once

#include "IMeasurementAggregationStrategy.h"

namespace Measurement
{
    class MaximumStrategy final : public IMeasurementAggregationStrategy
    {
    public:
        float Aggregate(float nextValue) override;
        void Reset() override;

        float _currentAggregate = 0;
        bool _isFirstCall = true;
    };
}
