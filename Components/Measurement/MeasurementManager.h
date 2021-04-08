#pragma once

#include "IMeasurementAggregationStrategy.h"
#include "IMeasurementManager.h"
#include "IMeasurementContainer.h"
#include "../Time/ITimeConverter.h"

namespace Measurement
{
    class MeasurementManager final : public IMeasurementManager
    {
    public:
        MeasurementManager(
            IMeasurementContainer& container,
            IMeasurementAggregationStrategy& aggregationStrategy,
            Time::ITimeConverter& timeConverter,
            const time_t intervalDuration,
            char* sensorId)
            :
            _container(container),
            _aggregationStrategy(aggregationStrategy),
            _timeConverter(timeConverter),
            _intervalDuration(intervalDuration),
            _sensorId(sensorId)
        {
        }
        void Record(float value, time_t measurementTime) override;
        void SetInterval(time_t interval) override;

    private:
        IMeasurementContainer& _container;
        IMeasurementAggregationStrategy& _aggregationStrategy;
        Time::ITimeConverter& _timeConverter;
        time_t _intervalDuration;
        time_t _intervalStart = 0;
        char* _sensorId;
        float _intervalAggregate = 0;
    };
}
