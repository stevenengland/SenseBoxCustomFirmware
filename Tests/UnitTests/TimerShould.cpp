#include <gtest.h>
#include <gmock.h>
#include "ElapsedTimeProviderMock.hpp"
#include "Timer.h"

using namespace testing;

namespace TimeTests
{
    class TimerShould : public Test {
    public:
        Time::ElapsedTimeProviderMock ElapsedTimeProviderMock{};
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
            .WillOnce(Return(10001)) // 10000 was the limit
            .WillOnce(Return(20001)); // 20000 was the limit
        Timer.HasIntervalElapsed();
        ASSERT_TRUE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnTrue_IfTimeHasElapsed_AfterMillisRollover) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(4294967290)) // true, 5ms before rollover
            .WillOnce(Return(10)) // false, 10ms after rollover
            .WillOnce(Return(500)) // false
            .WillOnce(Return(10001)); // true

        const auto test1 = static_cast<unsigned long>(500 - 4294967290);
        const auto test2 = static_cast<unsigned long>(10001 - 4294967290);

        ASSERT_EQ(static_cast<unsigned long>(506), test1);
        ASSERT_EQ(static_cast<unsigned long>(10007), test2);
        ASSERT_TRUE(Timer.HasIntervalElapsed());
        ASSERT_FALSE(Timer.HasIntervalElapsed());
        ASSERT_FALSE(Timer.HasIntervalElapsed());
        ASSERT_TRUE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnFalse_IfTimeHasElapsedButTimerWasResetInTheMeanwhile) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(9998))   // has elapsed?
            .WillOnce(Return(9999))   // reset
            .WillOnce(Return(10001)); // has elapsed?

        ASSERT_FALSE(Timer.HasIntervalElapsed());
        Timer.Reset();
        ASSERT_FALSE(Timer.HasIntervalElapsed());
    }

    TEST_F(TimerShould, ReturnTrue_IfTimeHasElapsedAfterTimerWasReset) {
        EXPECT_CALL(ElapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(9998)) // has elapsed?
            .WillOnce(Return(9999)) // reset
            .WillOnce(Return(20000)); // has elapsed?

        ASSERT_FALSE(Timer.HasIntervalElapsed());
        Timer.Reset();
        ASSERT_TRUE(Timer.HasIntervalElapsed());
    }
}
