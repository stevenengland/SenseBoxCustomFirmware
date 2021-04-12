#include <gtest.h>
#include <gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "ElapsedTimeProviderMock.hpp"
#include "gmock-matchers.h"
#include "gmock-spec-builders.h"
#include "MeasurementContainerMock.hpp"
#include "MeasurementManagerMock.hpp"
#include "SenseBoxIoMapperMock.hpp"
#include "WatchDogMock.hpp"
#include "SenseboxMcuSketchCoupling.h"
#include "SoundLevelMeterMock.hpp"
#include "TimeProviderMock.hpp"
#include "WifiManagerMock.hpp"

using namespace testing;

namespace SenseboxMcuSketchCouplingTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    protected:
        Sketch::SketchConfiguration _configuration = []
        {
            Sketch::SketchConfiguration c{};
            
            c.TimeProvider_TimeRequest_RetryInterval = 1000;
            c.TimeProvider_TimeRequest_RetryCount = 5;
            c.NetworkProvider_ConnectionRequest_RetryInterval = 1000;
            c.NetworkProvider_ConnectionRequest_RetryCount = 20;
            c.WatchDog_KeepAlive_TimeoutInterval = 16000;
            c.Sensor_Measure_Interval = 60000;
            c.SoundLevelMeter_Measure_Interval = 300;
            c.Osem_Upload_Interval = 300000;

            return c;
        }();
        /*{
            .TimeProvider_TimeRequest_RetryInterval = 1000
        };*/
        /*{
            .TimeProvider_TimeRequest_RetryInterval = 1000
        }*/

        Peripherals::SenseBoxIoMapperMock _senseBoxIoMapperMock;
        Time::WatchDogMock _watchDogMock;
        Time::ElapsedTimeProviderMock _elapsedTimeProviderMock;
        Time::TimeProviderMock _timeProviderMock;
        Peripherals::AnalogPortReaderMock _analogPortReaderMock;
        Sensor::SoundLevelMeterMock _soundLevelMeterMock;
        Measurement::MeasurementContainerMock _measurementContainerMock;
        Measurement::MeasurementManagerMock _measurementManagerMock;
        Network::Wifi::WifiManagerMock _wifiManagerMock;
        Sketch::SenseboxMcuSketchCoupling _sketchCoupling
        {
            _senseBoxIoMapperMock,
            _watchDogMock,
            _elapsedTimeProviderMock,
            _timeProviderMock,
            _soundLevelMeterMock,
            _measurementContainerMock,
            _measurementManagerMock,
            _wifiManagerMock,
            _configuration
        };
    };

    TEST_F(SenseboxMcuSketchCouplingShould, BringUpAllPins_WhenSetupIsCalled)
    {
        EXPECT_CALL(_senseBoxIoMapperMock, PowerAll()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, EnableWatchDog_WhenSetupEnds)
    {
        InSequence s; // Force sequence of upcoming calls.
        EXPECT_CALL(_watchDogMock, Disable()).Times(1);
        EXPECT_CALL(_watchDogMock, Enable(_)).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenLoopEnds)
    {
        EXPECT_CALL(_watchDogMock, Reset()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetDevice_WhenNetworkCouldNotBeEstablished)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(false));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(1));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_)).Times(_configuration.NetworkProvider_ConnectionRequest_RetryCount);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(Ge(_configuration.WatchDog_KeepAlive_TimeoutInterval))).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenNetworkCouldNotBeEstablished)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(false));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(1));
        EXPECT_CALL(_watchDogMock, Reset()).Times(_configuration.NetworkProvider_ConnectionRequest_RetryCount);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetDevice_WhenTimeCouldNotBeDetermined)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(true));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(0));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_)).Times(_configuration.TimeProvider_TimeRequest_RetryCount);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(Ge(_configuration.WatchDog_KeepAlive_TimeoutInterval))).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenTimeCouldNotBeDetermined)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(true));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(0));
        EXPECT_CALL(_watchDogMock, Reset()).Times(_configuration.TimeProvider_TimeRequest_RetryCount);

        _sketchCoupling.Setup();
    }
}
