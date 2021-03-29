#pragma once

#include "Measurement.h"

namespace Measurement
{
    class MeasurementContainer
    {
    public:
        virtual ~MeasurementContainer() = default;
        
        virtual void AddMeasurement(Measurement &measurement) = 0;
        virtual void RemoveMeasurements(int count) = 0;
        virtual Measurement* GetAllMeasurements();
    };
}
