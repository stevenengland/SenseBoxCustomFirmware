#pragma once

#include "IMeasurementConverter.h"
#include "ITimeConverter.h"

namespace Measurement
{
    class MeasurementToCsvLineConverter final : public IMeasurementConverter
    {
    public:
        explicit MeasurementToCsvLineConverter(Time::ITimeConverter& timeConverter)
            : _timeConverter(timeConverter)
        {
        }
        int Convert(Measurement& measurement, char* convertedMeasurement) override;
    private:
        Time::ITimeConverter& _timeConverter;
    };
}
