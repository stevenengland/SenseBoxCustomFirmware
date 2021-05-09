#pragma once

#include "IMeasurementConverter.h"
#include "IMeasurmentUploader.h"
#include "../Network/IHttpTerminal.h"

namespace Measurement
{
    class MeasurementToOsemUploader final : public IMeasurementUploader
    {
    public:
        MeasurementToOsemUploader(
            Network::IHttpTerminal& httpTerminal,
            IMeasurementConverter& measurementConverter,
            const char* hostName,
            uint16_t port,
            const char* boxId,
            const char* authToken
            )
                : _httpTerminal(httpTerminal),
                  _measurementConverter(measurementConverter),
                  _hostName(hostName),
                  _port(port),
                  _boxId(boxId),
                  _authToken(authToken)
        {
        }

        TransmissionStatus TrySendUpload(IMeasurementContainer& container) override;
        TransmissionStatus ReadUploadResponse(char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout = 5000) override;
        ProcessingStatus TryExtractUploadSuccess(char* responseBuffer, size_t lengthOfResponseBuffer) override;
        void EndUpload() override;
    private:
        Network::IHttpTerminal& _httpTerminal;
        IMeasurementConverter& _measurementConverter;
        const char* _hostName;
        uint16_t _port;
        const char* _boxId;
        const char* _authToken;
    };
}
