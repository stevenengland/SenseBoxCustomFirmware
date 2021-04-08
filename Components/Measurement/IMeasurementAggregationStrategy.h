#pragma once

namespace Measurement
{
    class IMeasurementAggregationStrategy
    {
    public:
        virtual ~IMeasurementAggregationStrategy() = default;

        virtual float Aggregate(float currentAggregate, float nextValue) = 0;
    };
}
