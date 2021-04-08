#include <string>
#include "../../Components/Measurement/MaximumStrategy.h"
#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"

using namespace testing;

namespace MeasurementAggregationStrategyTests
{
    class MaximumStrategyShould :public Test {
    protected:
        Measurement::MaximumStrategy _strategy;
    };

    TEST_F(MaximumStrategyShould, ReturnCorrectMax_GivenMultipleValuesWithoutOrdering)
    {
        float currentAggregate = 0;

        currentAggregate = _strategy.Aggregate(currentAggregate, 2);
        currentAggregate = _strategy.Aggregate(currentAggregate, 6);
        currentAggregate = _strategy.Aggregate(currentAggregate, 3);

        ASSERT_FLOAT_EQ(currentAggregate, 6);
    }
}
