#pragma once

#include <cstdint>
#include "IMeasurementContainer.h"
#include "TransmissionStatus.h"
#include "ProcessingStatus.h"

namespace Measurement
{
    class IMeasurementUploader
    {
    public:
        virtual ~IMeasurementUploader() = default;

        virtual TransmissionStatus TrySendUpload(IMeasurementContainer& container) = 0;
        virtual TransmissionStatus ReadUploadResponse(char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout = 5000) = 0;
        virtual ProcessingStatus TryExtractUploadSuccess(char* responseBuffer, size_t lengthOfResponseBuffer) = 0;
        virtual void EndUpload() = 0;
    };
}
