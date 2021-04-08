#include "MaximumStrategy.h"

namespace Measurement
{
    float MaximumStrategy::Aggregate(float currentAggregate, float nextValue)
    {
        return (currentAggregate > nextValue) ? currentAggregate : nextValue;
    }
}
