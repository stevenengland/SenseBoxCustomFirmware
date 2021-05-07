#pragma once

#include "IHttpTerminal.h"
#include "ITcpStream.h"
#include "IElapsedTimeProvider.h"

namespace Network
{
    class HttpTerminal final : public IHttpTerminal
    {
    public:
        explicit HttpTerminal(
            ITcpStream& tcpStream,
            Time::IElapsedTimeProvider& elapsedTimeProvider)
            : _tcpStream(tcpStream),
              _elapsedTimeProvider(elapsedTimeProvider)
        { 
        }

        bool TryConnect(const char* host, uint16_t port, bool useSsl = true) override;
        size_t SendRequestLine(const char* httpVerb, const char* requestUri, const char* httpVersion) override;
        size_t SendHeader(const char* headerName, const char* headerValue) override;
        TransmissionStatus ReadResponse(char* responseBuffer, size_t lengthOfResponseBuffer, unsigned long timeout = 5000) override;
        size_t SendBody(const char* payload) override;
        size_t SendEmptyLine() override;
        void CloseConnection() override;
        int TryExtractHttpStatusCode(char* responseBuffer, size_t lengthOfResponseBuffer) override;
    private:
        ITcpStream& _tcpStream;
        Time::IElapsedTimeProvider& _elapsedTimeProvider;
        const char _emptyLine[3] = "\r\n";
        const char _lineEnding[3] = "\r\n";
        const char _space[2] = " ";
    };
}
