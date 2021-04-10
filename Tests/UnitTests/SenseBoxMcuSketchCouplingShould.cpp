#include <gtest.h>
#include <gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "ElapsedTimeProviderMock.hpp"
#include "MeasurementContainerMock.hpp"
#include "MeasurementManagerMock.hpp"
#include "WatchDogMock.hpp"
#include "SenseboxMcuSketchCoupling.h"
#include "SoundLevelMeterMock.hpp"
#include "TimeProviderMock.hpp"

using namespace testing;

namespace SenseboxMcuSketchCouplingTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    public:
        Time::WatchDogMock WatchDogMock;
        Time::ElapsedTimeProviderMock ElapsedTimeProviderMock;
        Time::TimeProviderMock TimeProviderMock;
        Peripherals::AnalogPortReaderMock AnalogPortReaderMock;
        Sensor::SoundLevelMeterMock SoundLevelMeterMock;
        Measurement::MeasurementContainerMock MeasurementContainerMock;
        Measurement::MeasurementManagerMock MeasurementManagerMock;
        Sketch::SenseboxMcuSketchCoupling SketchCoupling
        {
            WatchDogMock,
            ElapsedTimeProviderMock,
            TimeProviderMock,
            SoundLevelMeterMock,
            MeasurementContainerMock,
            MeasurementManagerMock
        };
    };

    TEST_F(SenseboxMcuSketchCouplingShould, EnableWatchDog_WhenSetupEnds)
    {
        EXPECT_CALL(WatchDogMock, Enable(_)).Times(1);

        SketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenLoopEnds)
    {
        EXPECT_CALL(WatchDogMock, Reset()).Times(1);

        SketchCoupling.Loop();
    }
}
