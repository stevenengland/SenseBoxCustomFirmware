#pragma once

#include <gmock.h>

#include "../../Components/Network/IHttpTerminal.h"

namespace Network
{
    class HttpTerminalMock final : public IHttpTerminal
    {
    public:
        MOCK_METHOD(bool, TryConnect, (const char* host, uint16_t port, bool useSsl), (override));
        MOCK_METHOD(size_t, SendRequestLine, (const char* httpVerb, const char* requestUri, const char* httpVersion), (override));
        MOCK_METHOD(size_t, SendHeader, (const char* headerName, const char* headerValue), (override));
        MOCK_METHOD(size_t, SendBody, (const char* payload), (override));
        MOCK_METHOD(size_t, SendEmptyLine, (), (override));
        MOCK_METHOD(TransmissionStatus, ReadResponse, (char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout), (override));
        MOCK_METHOD(int, TryExtractHttpStatusCode, (char* responseBuffer, size_t lengthOfResponseBuffer), (override));
        MOCK_METHOD(void, CloseConnection, (), (override));
    };
}
