#pragma once

#include <gmock.h>

#include "../../Components/Measurement/IMeasurmentUploader.h"

namespace Measurement
{
    class MeasurementUploaderMock final : public IMeasurementUploader
    {
    public:
        MOCK_METHOD(TransmissionStatus, TrySendUpload, (IMeasurementContainer& container), (override));
        MOCK_METHOD(TransmissionStatus, ReadUploadResponse, (char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout), (override));
        MOCK_METHOD(ProcessingStatus, TryExtractUploadSuccess, (char* responseBuffer, size_t lengthOfResponseBuffer), (override));
        MOCK_METHOD(void, EndUpload, (), (override));
    };
}
