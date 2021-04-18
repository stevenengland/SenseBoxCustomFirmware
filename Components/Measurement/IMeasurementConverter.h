#pragma once

#include "Measurement.h"

namespace Measurement
{
    class IMeasurementConverter
    {
    public:
        virtual ~IMeasurementConverter() = default;

        virtual int Convert(Measurement& measurement, char* convertedMeasurement) = 0;
    };
}
