#include <stdio.h>
#include "MeasurementToCsvLineConverter.h"

namespace Measurement
{
    int MeasurementToCsvLineConverter::Convert(Measurement& measurement, char* convertedMeasurement)
    {
        char utcTime[21]{};
        _timeConverter.GetUtcTime(measurement.Timestamp, utcTime);
        const auto n = sprintf(convertedMeasurement, "%s,%9.2f,%s\n", measurement.SensorId, measurement.Value, utcTime);
        return n;
    }
}
