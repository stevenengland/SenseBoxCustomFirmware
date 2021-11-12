#include <gmock.h>
#include <gtest.h>

#include "AnalogPortReaderMock.hpp"
#include "ElapsedTimeProviderMock.hpp"
#include "gmock-matchers.h"
#include "gmock-spec-builders.h"
#include "LoggerMock.hpp"
#include "LogLevel.h"
#include "MeasurementContainerMock.hpp"
#include "MeasurementRecorderMock.hpp"
#include "MeasurementUploaderMock.hpp"
#include "RamInfoReaderMock.hpp"
#include "SenseBoxIoMapperMock.hpp"
#include "SenseboxMcuSketchCoupling.h"
#include "SensorMock.hpp"
#include "HibernatableSensorMock.hpp"
#include "TimeProviderMock.hpp"
#include "WatchDogMock.hpp"
#include "WifiManagerMock.hpp"

using namespace testing;

namespace SketchTests
{
    class SenseboxMcuSketchCouplingShould : public Test
    {
    protected:
        int _standardInterval = 9999;
        int _ltStandardInterval = 5000;
        Sketch::SketchConfiguration _configuration = [&]
        {
            Sketch::SketchConfiguration c{};

            c.Logger_LogLevel = LogLevelVerbose;
            c.TimeProvider_TimeRequest_RetryInterval = _standardInterval;
            c.TimeProvider_TimeRequest_RetryCount = 5;
            c.NetworkProvider_ConnectionRequest_RetryInterval = _standardInterval;
            c.NetworkProvider_ConnectionRequest_RetryCount = 20;
            c.NetworkProvider_ConnectionStatus_CheckInterval = _standardInterval;
            c.WatchDog_KeepAlive_TimeoutInterval = _standardInterval;
            c.MeasurementContainer_Capacity = 1000;
            c.Sensor_Measure_Interval = _standardInterval;
            c.Sensor_Measure_AggregationInterval = 1;
            c.SoundLevelMeter_Measure_Interval = 300;
            c.SoundLevelMeter_Measure_AggregationInterval = 1;
            c.FineDustSensor_Measure_Interval = _standardInterval;
            c.Osem_Upload_Interval = _standardInterval;
            c.Osem_Upload_Interval_ErrorCondition = _ltStandardInterval;
            c.HealthCheck_Interval = _standardInterval;

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
        Sensor::SensorMock _soundLevelMeterMock;
        Sensor::SensorMock _temperatureSensorMock;
        Sensor::SensorMock _humiditySensorMock;
        Sensor::HibernatableSensorMock _fineDustSensorMock;
        Measurement::MeasurementContainerMock _measurementContainerMock;
        Measurement::MeasurementRecorderMock _slmMeasurementRecorderMock;
        Measurement::MeasurementRecorderMock _temperatureMeasurementRecorderMock;
        Measurement::MeasurementRecorderMock _humidityMeasurementRecorderMock;
        Measurement::MeasurementRecorderMock _fineDustP25MeasurementRecorderMock;
        Measurement::MeasurementRecorderMock _fineDustP10MeasurementRecorderMock;
        Measurement::MeasurementUploaderMock _measurementUploaderMock;
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
            _temperatureSensorMock,
            _humiditySensorMock,
            _fineDustSensorMock,
            _measurementContainerMock,
            _slmMeasurementRecorderMock,
            _temperatureMeasurementRecorderMock,
            _humidityMeasurementRecorderMock,
            _fineDustP25MeasurementRecorderMock,
            _fineDustP10MeasurementRecorderMock,
            _measurementUploaderMock,
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
        _configuration.WatchDog_KeepAlive_TimeoutInterval = _standardInterval + 10;
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(false));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(1));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(5000)).Times(1);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(2000)).Times(1);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_configuration.NetworkProvider_ConnectionRequest_RetryInterval)).Times(_configuration.NetworkProvider_ConnectionRequest_RetryCount);
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
        _configuration.WatchDog_KeepAlive_TimeoutInterval = _standardInterval + 10;
        ON_CALL(_wifiManagerMock, IsConnected()).WillByDefault(Return(true));
        ON_CALL(_timeProviderMock, GetEpochTime()).WillByDefault(Return(0));
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(5000)).Times(1);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(2000)).Times(1);
        EXPECT_CALL(_elapsedTimeProviderMock, WaitSync(_configuration.TimeProvider_TimeRequest_RetryInterval)).Times(_configuration.TimeProvider_TimeRequest_RetryCount);
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
        EXPECT_CALL(_wifiManagerMock, IsConnected()).WillRepeatedly(Return(false));
        EXPECT_CALL(_wifiManagerMock, Reconnect()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, CheckWifi_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.NetworkProvider_ConnectionStatus_CheckInterval + 1));
        EXPECT_CALL(_wifiManagerMock, IsConnected()).WillRepeatedly(Return(true));
        EXPECT_CALL(_wifiManagerMock, Reconnect()).Times(0);

        _sketchCoupling.Loop();
    }

#pragma endregion Network

#pragma region Logging

    TEST_F(SenseboxMcuSketchCouplingShould, StartLogging_DuringSetup)
    {
        EXPECT_CALL(_loggerMock, Begin()).Times(2); // Initial start and health check at the end of setup

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RestartLogging_DuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.HealthCheck_Interval + 1));
        EXPECT_CALL(_loggerMock, Begin()).Times(1);

        _sketchCoupling.Loop();
    }

#pragma endregion Logging

#pragma region Measurement

    TEST_F(SenseboxMcuSketchCouplingShould, InitializeSoundSensor_DuringSetup)
    {
        EXPECT_CALL(_soundLevelMeterMock, Init()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, InitializeTemperatureSensor_DuringSetup)
    {
        EXPECT_CALL(_temperatureSensorMock, Init()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, InitializeHumiditySensor_DuringSetup)
    {
        EXPECT_CALL(_humiditySensorMock, Init()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, InitializeFineDustSensor_DuringSetup)
    {
        EXPECT_CALL(_fineDustSensorMock, Init()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, SendFineDustSensorToSleep_DuringSetup)
    {
        EXPECT_CALL(_fineDustSensorMock, Sleep()).Times(1);

        _sketchCoupling.Setup();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RecordSound_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.SoundLevelMeter_Measure_Interval + 1));
        EXPECT_CALL(_slmMeasurementRecorderMock, Record(_,_)).Times(1);
        EXPECT_CALL(_soundLevelMeterMock, ReadValue(_)).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, NotRecordSound_WhenSensorReturnedNan_DuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.SoundLevelMeter_Measure_Interval + 1));
        EXPECT_CALL(_slmMeasurementRecorderMock, Record(_, _)).Times(0);
        EXPECT_CALL(_soundLevelMeterMock, ReadValue(_)).Times(1).WillOnce(Return(NAN));

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RecordTemperature_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Sensor_Measure_Interval + 1));
        EXPECT_CALL(_temperatureMeasurementRecorderMock, Record(_,_)).Times(1);
        EXPECT_CALL(_temperatureSensorMock, ReadValue(_)).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, NotRecordTemperature_WhenSensorReturnedNan_DuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Sensor_Measure_Interval + 1));
        EXPECT_CALL(_temperatureMeasurementRecorderMock, Record(_, _)).Times(0);
        EXPECT_CALL(_temperatureSensorMock, ReadValue(_)).Times(1).WillOnce(Return(NAN));

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RecordHumdity_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Sensor_Measure_Interval + 1));
        EXPECT_CALL(_humidityMeasurementRecorderMock, Record(_,_)).Times(1);
        EXPECT_CALL(_humiditySensorMock, ReadValue(_)).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, NotRecordHumdity_WhenSensorReturnedNan_DuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Sensor_Measure_Interval + 1));
        EXPECT_CALL(_humidityMeasurementRecorderMock, Record(_, _)).Times(0);
        EXPECT_CALL(_humiditySensorMock, ReadValue(_)).Times(1).WillOnce(Return(NAN));

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RecordPm25_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval + 1));
        EXPECT_CALL(_fineDustP25MeasurementRecorderMock, Record(_,_)).Times(1);
        EXPECT_CALL(_fineDustSensorMock, ReadValues()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, NotRecordPm25_WhenSensorReturnedNan_DuringLoop)
    {
        Sensor::SensorReads reads{};
        reads.Reads[0] = NAN;
        reads.Reads[1] = NAN;
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval + 1));
        EXPECT_CALL(_fineDustP25MeasurementRecorderMock, Record(_, _)).Times(0);
        EXPECT_CALL(_fineDustSensorMock, ReadValues()).Times(1).WillOnce(Return(reads));

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, RecordPm10_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval + 1));
        EXPECT_CALL(_fineDustP10MeasurementRecorderMock, Record(_,_)).Times(1);
        EXPECT_CALL(_fineDustSensorMock, ReadValues()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, NotRecordPm10_WhenSensorReturnedNan_DuringLoop)
    {
        Sensor::SensorReads reads{};
        reads.Reads[0] = NAN;
        reads.Reads[1] = NAN;
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval + 1));
        EXPECT_CALL(_fineDustP10MeasurementRecorderMock, Record(_, _)).Times(0);
        EXPECT_CALL(_fineDustSensorMock, ReadValues()).Times(1).WillOnce(Return(reads));

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, SendFineDustSensorToSleep_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval + 1));
        EXPECT_CALL(_fineDustSensorMock, Sleep()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, WakeupFineDustSensor_WhenIntervalElapsedDuringLoop)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.FineDustSensor_Measure_Interval - 60000 + 1));
        EXPECT_CALL(_fineDustSensorMock, Wakeup()).Times(1);

        _sketchCoupling.Loop();
    }

#pragma endregion Measurement

#pragma region MeasurementUpload

    TEST_F(SenseboxMcuSketchCouplingShould, ClearMeasurements_IfUploadWasProcessedSuccessfully)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Osem_Upload_Interval + 1));
        ON_CALL(_measurementUploaderMock, TrySendUpload(_)).WillByDefault(Return(Completed));
        ON_CALL(_measurementUploaderMock, ReadUploadResponse(_, _, _)).WillByDefault(Return(Completed));
        ON_CALL(_measurementUploaderMock, TryExtractUploadSuccess(_, _)).WillByDefault(Return(Success));
        EXPECT_CALL(_measurementContainerMock, ClearMeasurements()).Times(1);

        _sketchCoupling.Loop();
    }

    TEST_F(SenseboxMcuSketchCouplingShould, FinalizeUpload_InAnyCase)
    {
        ON_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds()).WillByDefault(Return(_configuration.Osem_Upload_Interval + 1));
        ON_CALL(_measurementUploaderMock, TrySendUpload(_)).WillByDefault(Return(Completed));
        ON_CALL(_measurementUploaderMock, ReadUploadResponse(_, _, _)).WillByDefault(Return(Completed));
        ON_CALL(_measurementUploaderMock, TryExtractUploadSuccess(_, _)).WillByDefault(Return(Success));
        EXPECT_CALL(_measurementContainerMock, ClearMeasurements()).Times(1);

        _sketchCoupling.Loop();
    }

#pragma endregion MeasurementUpload

}
