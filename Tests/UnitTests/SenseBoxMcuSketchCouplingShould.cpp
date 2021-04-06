#include <gtest.h>
#include <gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "ElapsedTimeProviderMock.hpp"
#include "MeasurementContainerMock.hpp"
#include "WatchDogMock.hpp"
#include "SenseboxMcuSketchCoupling.h"
#include "SoundLevelMeterMock.hpp"

using namespace testing;

namespace SenseboxMcuSketchCouplingTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    public:
        Time::WatchDogMock WatchDogMock;
        Time::ElapsedTimeProviderMock ElapsedTimeProviderMock;
        Peripherals::AnalogPortReaderMock AnalogPortReaderMock;
        SoundLevelMeter::SoundLevelMeterMock SoundLevelMeterMock;
        Measurement::MeasurementContainerMock MeasurementContainerMock;
        Sketch::SenseboxMcuSketchCoupling SketchCoupling
        {
            WatchDogMock,
            ElapsedTimeProviderMock,
            SoundLevelMeterMock,
            MeasurementContainerMock
        };
    };

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenLoopEnds)
    {
        EXPECT_CALL(WatchDogMock, Reset()).Times(1);

        SketchCoupling.Loop();
    }
}
