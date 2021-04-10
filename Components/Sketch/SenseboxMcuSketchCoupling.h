#pragma once

#include "ISketchCoupling.h"
#include "IWatchDog.h"
#include "Timer.h"
#include "IElapsedTimeProvider.h"
#include "IMeasurementContainer.h"
#include "ISensor.h"
#include "IMeasurementManager.h"
#include "ITimeProvider.h"

namespace Sketch
{
    class SenseboxMcuSketchCoupling final : public ISketchCoupling
    {
    public:
        SenseboxMcuSketchCoupling(
            Time::IWatchDog& watchDog,
            Time::IElapsedTimeProvider& elapsedTimeProvider,
            Time::ITimeProvider& timeProvider,
            Sensor::ISensor& soundLevelMeter,
            Measurement::IMeasurementContainer& measurementContainer,
            Measurement::IMeasurementManager& slmMeasurementManager)
            : _watchDog(watchDog),
              _elapsedTimeProvider(elapsedTimeProvider),
              _timeProvider(timeProvider),
              _soundLevelMeter(soundLevelMeter),
              _measurementContainer(measurementContainer),
              _slmMeasurementManager(slmMeasurementManager),
              _soundLevelMeasurementTimer(_elapsedTimeProvider, 300),
              _generalMeasurementTimer(_elapsedTimeProvider, 60000),
              _uploadToOsemTimer(_elapsedTimeProvider, 300000)
        {
        }

        void Setup() override;
        void Loop() override;
    private:
        Time::IWatchDog& _watchDog;
        Time::IElapsedTimeProvider& _elapsedTimeProvider;
        Time::ITimeProvider& _timeProvider;
        Sensor::ISensor& _soundLevelMeter;
        Measurement::IMeasurementContainer& _measurementContainer;
        Measurement::IMeasurementManager& _slmMeasurementManager;
        //Time::Timer _soundLevelMeasurementTimer{ _elapsedTimeProvider, 300 };
        //Time::Timer _generalMeasurementTimer{ _elapsedTimeProvider, 60000 };
        //Time::Timer _uploadToOsemTimer{ _elapsedTimeProvider, 300000 };
        Time::Timer _soundLevelMeasurementTimer;
        Time::Timer _generalMeasurementTimer;
        Time::Timer _uploadToOsemTimer;

        bool CheckTimeProvider(int retryCounter) const;
    };
}
