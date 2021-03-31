#include <gtest.h>
#include <gmock.h>
#include "ElapsedTimeProviderMock.hpp"
#include "Timer.h"

using namespace testing;

namespace TimeTests
{
    class TimerShould : public Test {
    public:
        Time::ElapsedTimeProviderMock ElapsedTimeProviderMock;
        Time::Timer Timer{ElapsedTimeProviderMock, 10000};
    };

    TEST_F(TimerShould, ReturnFalse_IfTimeHasNotElapsed) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds()).WillOnce(Return(9999));
        ASSERT_FALSE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnFalse_IfTimeHasNotElapsedAfterItElapsedOnce) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(10001))
            .WillOnce(Return(19999));
        Timer.HasIntervalElapsed();
        ASSERT_FALSE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnTrue_IfTimeHasElapsed) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds()).WillOnce(Return(10001));
        ASSERT_TRUE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnTrue_IfTimeHasElapsedAfterItElapsedOnce) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(10001))
            .WillOnce(Return(20002));
        Timer.HasIntervalElapsed();
        ASSERT_TRUE(Timer.HasIntervalElapsed());
    }
}
