#include <gtest.h>
#include <gmock.h>
#include "ElapsedTimeProviderMock.hpp"
#include "WatchDogMock.hpp"
#include "SenseboxMcuSketchCoupling.h"

using namespace testing;

namespace SenseboxMcuSketchCouplingTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    public:
        Time::WatchDogMock WatchDogMock;
        Time::ElapsedTimeProviderMock ElapsedTimeProviderMock;
        Sketch::SenseboxMcuSketchCoupling SketchCoupling
        {
            WatchDogMock,
            ElapsedTimeProviderMock
        };
    };

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenLoopEnds)
    {
        EXPECT_CALL(WatchDogMock, Reset()).Times(1);

        SketchCoupling.Loop();
    }
}
