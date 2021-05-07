#pragma once
#include <cstdint>
#include <ctime>

#include "TransmissionStatus.h"

namespace Network
{
    class IHttpTerminal
    {
    public:
        virtual ~IHttpTerminal() = default;

        virtual bool TryConnect(const char* host, uint16_t port, bool useSsl = true) = 0;
        virtual size_t SendRequestLine(const char* httpVerb, const char* requestUri, const char* httpVersion) = 0;
        virtual size_t SendHeader(const char* headerName, const char* headerValue) = 0;
        virtual size_t SendBody(const char* payload) = 0;
        virtual size_t SendEmptyLine() = 0;
        virtual TransmissionStatus ReadResponse(char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout = 5000) = 0;
        virtual int TryExtractHttpStatusCode(char* responseBuffer, size_t lengthOfResponseBuffer) = 0;
        virtual void CloseConnection() = 0;
    };
}
