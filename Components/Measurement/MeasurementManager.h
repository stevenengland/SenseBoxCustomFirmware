#pragma once

#include "IMeasurementAggregationStrategy.h"
#include "IMeasurementManager.h"
#include "IMeasurementContainer.h"
#include "ITimeConverter.h"

namespace Measurement
{
    class MeasurementManager final : public IMeasurementManager
    {
    public:
        MeasurementManager(
            IMeasurementContainer& container,
            IMeasurementAggregationStrategy& aggregationStrategy,
            const time_t intervalDuration,
            const char* sensorId)
            :
            _container(container),
            _aggregationStrategy(aggregationStrategy),
            _intervalDuration(intervalDuration),
            _sensorId(sensorId)
        {
        }
        void Record(float value, time_t measurementTime) override;
        void SetInterval(time_t interval) override;

    private:
        IMeasurementContainer& _container;
        IMeasurementAggregationStrategy& _aggregationStrategy;
        time_t _intervalDuration;
        time_t _intervalStart = 0;
        const char* _sensorId;
        float _intervalAggregate = 0;
    };
}
