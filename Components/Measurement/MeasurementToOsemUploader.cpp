#include "MeasurementToOsemUploader.h"
#include <cstdio>

namespace Measurement
{
    TransmissionStatus MeasurementToOsemUploader::TrySendUpload(IMeasurementContainer& container)
    {
        if (!_httpTerminal.TryConnect(_hostName, _port, true))
        {
            return ConnectionError;
        }

        char rqlBuffer[80]{};
        sprintf(rqlBuffer, "/boxes/%s/data", _boxId);
        if(_httpTerminal.SendRequestLine("POST", rqlBuffer, "HTTP/1.1") < 1)
        {
            return TransmissionError;
        };

        auto const contentLength = container.Count() * 56;
        char clBuffer[5]{};
        sprintf(clBuffer, "%d", contentLength);
        _httpTerminal.SendHeader("Connection", "close");
        _httpTerminal.SendHeader("Authorization", _authToken);
        _httpTerminal.SendHeader("Host", _hostName);
        _httpTerminal.SendHeader("Content-Type", "text/csv");
        _httpTerminal.SendHeader("Content-Length", clBuffer);
        _httpTerminal.SendEmptyLine();

        char measurementBuffer[100]{}; // ToDo: Do I want to empty it in the loop?
        for (auto i = 0; i < container.Count(); ++i)
        {
            Measurement measurement{};
            if (!container.GetMeasurement(i, measurement))
            {
                continue;
            }

            const auto length = _measurementConverter.Convert(measurement, measurementBuffer);
            _httpTerminal.SendBody(measurementBuffer);
        }

        if (_httpTerminal.SendEmptyLine() < 1)
        {
            return TransmissionError;
        };

        return Completed;
    }

    TransmissionStatus MeasurementToOsemUploader::ReadUploadResponse(char* responseBuffer, size_t lengthOfResponseBuffer, const unsigned long timeout)
    {
        return _httpTerminal.ReadResponse(responseBuffer, lengthOfResponseBuffer, timeout);
    }

    void MeasurementToOsemUploader::EndUpload()
    {
        _httpTerminal.CloseConnection();
    }
}
