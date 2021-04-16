#pragma once

namespace Measurement
{
    class IMeasurementAggregationStrategy
    {
    public:
        virtual ~IMeasurementAggregationStrategy() = default;

        virtual float Aggregate(float nextValue) = 0;
        virtual void Reset() = 0;
    };
}
