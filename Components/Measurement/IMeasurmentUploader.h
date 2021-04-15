#pragma once
#include "MeasurementContainer.h"

namespace Measurement
{
    class IMeasurementUploader
    {
    public:
        bool TryUpload(MeasurementContainer& container);
    };
}
