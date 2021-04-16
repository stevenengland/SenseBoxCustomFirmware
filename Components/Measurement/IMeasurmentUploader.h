#pragma once
#include "IMeasurementContainer.h"

namespace Measurement
{
    class IMeasurementUploader
    {
    public:
        bool TryUpload(IMeasurementContainer& container);
    };
}
