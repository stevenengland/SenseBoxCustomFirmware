#pragma once

#include <gmock.h>

#include "../../Components/Measurement/IMeasurementConverter.h"

namespace Measurement
{
    class MeasurementConverterMock final : public IMeasurementConverter
    {
    public:
         MOCK_METHOD(int, Convert, (Measurement& measurement, char* convertedMeasurement), (override));
    };
}
