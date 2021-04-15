#include <gtest.h>
#include <gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "ElapsedTimeProviderMock.hpp"
#include "gmock-matchers.h"
#include "gmock-spec-builders.h"
#include "LoggerMock.hpp"
#include "MeasurementContainerMock.hpp"
#include "MeasurementManagerMock.hpp"
#include "SenseBoxIoMapperMock.hpp"
#include "WatchDogMock.hpp"
#include "SenseboxMcuSketchCoupling.h"
#include "SoundLevelMeterMock.hpp"
#include "TimeProviderMock.hpp"
#include "WifiManagerMock.hpp"
#include "LogLevel.h"
#include "RamInfoReaderMock.hpp"

using namespace testing;

namespace SenseboxMcuSketchCouplingTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    protected:
        Sketch::SketchConfiguration _configuration = []
        {
            Sketch::SketchConfiguration c{};

            c.Logger_LogLevel = LogLevelVerbose;
            c.TimeProvider_TimeRequest_RetryInterval = 1000;
            c.TimeProvider_TimeRequest_RetryCount = 5;
            c.NetworkProvider_ConnectionRequest_RetryInterval = 1000;
            c.NetworkProvider_ConnectionRequest_RetryCount = 20;
            c.NetworkProvider_ConnectionStatus_CheckInterval = 30000;
            c.WatchDog_KeepAlive_TimeoutInterval = 16000;
            c.MeasurementContainer_Capacity = 1000;
            c.Sensor_Measure_Interval = 60000;
            c.SoundLevelMeter_Measure_Interval = 300;
            c.SoundLevelMeter_Measure_AggregationInterval = 1;
            c.Osem_Upload_Interval = 300000;
            c.HealthCheck_Interval = 360000;

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
        Measurement::MeasurementManagerMock _slmMeasurementManagerMock;
        Network::Wifi::WifiManagerMock _wifiManagerMock;
        CentralUnit::RamInfoReaderMock _ramInfoReaderMock;
        Logging::LoggerMock _loggerMock;
        Sketch::SenseboxMcuSketchCoupling _sketchCoupling
        {
            _senseBoxIoMapperMock,
            _watchDogMock,
            _elapsedTimeProviderMock,
            _timeProviderMock,
            _soundLevelMeterMock,
            _measurementContainerMock,
            _slmMeasurementManagerMock,
            _wifiManagerMock,
            _ramInfoReaderMock,
            _loggerMock,
            _configuration
        };
    };

#pragma region Keepalive

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

    TEST_F(SenseboxMcuSketchCouplingShould, ResetDevice_WhenNetworkCouldNotBeEstablishedDuringSetup)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(false));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(1));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_)).Times(_configuration.NetworkProvider_ConnectionRequest_RetryCount);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(Ge(_configuration.WatchDog_KeepAlive_TimeoutInterval))).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenNetworkCouldNotBeEstablishedDuringSetup)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(false));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(1));
        EXPECT_CALL(_watchDogMock, Reset()).Times(_configuration.NetworkProvider_ConnectionRequest_RetryCount);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetDevice_WhenTimeCouldNotBeDeterminedDuringSetup)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(true));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(0));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_)).Times(_configuration.TimeProvider_TimeRequest_RetryCount);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(Ge(_configuration.WatchDog_KeepAlive_TimeoutInterval))).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, ResetWatchDog_WhenTimeCouldNotBeDeterminedDuringSetup)
    {
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(true));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(0));
        EXPECT_CALL(_watchDogMock, Reset()).Times(_configuration.TimeProvider_TimeRequest_RetryCount);

        _sketchCoupling.Setup();
    }

#pragma endregion Keepalive

#pragma region Peripherals

    TEST_F(SenseboxMcuSketchCouplingShould, BringUpAllPins_WhenSetupIsCalled)
    {
        EXPECT_CALL(_senseBoxIoMapperMock, PowerAll()).Times(1);

        _sketchCoupling.Setup();
    }

#pragma endregion Peripherals

#pragma region Network

    TEST_F(SenseboxMcuSketchCouplingShould, TurnOnWifi_DuringSetup)
    {
        EXPECT_CALL(_wifiManagerMock, Connect()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, CheckWifiAndReconnect_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.NetworkProvider_ConnectionStatus_CheckInterval + 1));
        EXPECT_CALL(_wifiManagerMock, IsConnected()).WillOnce(Return(false));
        EXPECT_CALL(_wifiManagerMock, Reconnect()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, CheckWifi_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.NetworkProvider_ConnectionStatus_CheckInterval + 1));
        EXPECT_CALL(_wifiManagerMock, IsConnected()).WillOnce(Return(true));
        EXPECT_CALL(_wifiManagerMock, Reconnect()).Times(0);

        _sketchCoupling.Loop();
    }

#pragma endregion Network

#pragma region Measurement

    TEST_F(SenseboxMcuSketchCouplingShould, RecordSound_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.SoundLevelMeter_Measure_Interval + 1));
        EXPECT_CALL(_slmMeasurementManagerMock, Record(_,_)).Times(1);

        _sketchCoupling.Loop();
    }

#pragma endregion Measurement

}
