#include <string>
#include "../../Components/Measurement/MaximumStrategy.h"
#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"

using namespace testing;

namespace MeasurementTests
{
    class MaximumStrategyShould :public Test {
    protected:
        Measurement::MaximumStrategy _strategy;
    };

    TEST_F(MaximumStrategyShould, ReturnCorrectMax_WhenCalledTheFirstTime)
    {
        float currentAggregate = 0;

        currentAggregate = _strategy.Aggregate(2);

        ASSERT_FLOAT_EQ(currentAggregate, 2);
    }

    TEST_F(MaximumStrategyShould, ReturnCorrectMax_GivenMultipleValuesWithoutOrdering)
    {
        float currentAggregate = 0;

        currentAggregate = _strategy.Aggregate(2);
        currentAggregate = _strategy.Aggregate(6);
        currentAggregate = _strategy.Aggregate(3);

        ASSERT_FLOAT_EQ(currentAggregate, 6);
    }

    TEST_F(MaximumStrategyShould, ReturnCorrectMax_WhenFirstCalledAfterReset)
    {
        float currentAggregate = 0;

        currentAggregate = _strategy.Aggregate(3);
        currentAggregate = _strategy.Aggregate(6);
        currentAggregate = _strategy.Aggregate(4);
        _strategy.Reset();
        currentAggregate = _strategy.Aggregate(2);

        ASSERT_FLOAT_EQ(currentAggregate, 2);
    }
}
