#include "HttpTerminal.h"



#include <cctype>
#include <cstdlib>
#include <cstring>

namespace Network
{
    bool HttpTerminal::TryConnect(const char* host, const uint16_t port, const bool useSsl)
    {
        const auto success = _tcpStream.TryConnect(host, port, useSsl);

        if (!success)
        {
            _tcpStream.Stop();
        }

        return success;
    }

    size_t HttpTerminal::SendRequestLine(const char* httpVerb, const char* requestUri, const char* httpVersion)
    {
        size_t result = 0;
        result += _tcpStream.Transmit(httpVerb);
        result += _tcpStream.Transmit(_space);
        result += _tcpStream.Transmit(requestUri);
        result += _tcpStream.Transmit(_space);
        result += _tcpStream.Transmit(httpVersion);
        result += _tcpStream.Transmit(_lineEnding);

        return result;
    }

    size_t HttpTerminal::SendHeader(const char* headerName, const char* headerValue)
    {
        size_t result = 0;
        result += _tcpStream.Transmit(headerName);
        result += _tcpStream.Transmit(": ");
        result += _tcpStream.Transmit(headerValue);
        result += _tcpStream.Transmit(_lineEnding);

        return result;
    }

    TransmissionStatus HttpTerminal::ReadResponse(char* responseBuffer, const size_t lengthOfResponseBuffer, unsigned long timeout)
    {
        unsigned long startTime = _elapsedTimeProvider.ElapsedMilliseconds();
        while (!_tcpStream.IsAvailable()) 
        {
            if (_elapsedTimeProvider.ElapsedMilliseconds() - startTime > timeout)
            {
                _tcpStream.Stop();
                return Timeout;
            }
        }

        size_t count = 0;
        while (count < lengthOfResponseBuffer - 1 && _tcpStream.IsAvailable()) 
        {
            const auto c = _tcpStream.Receive();
            if (c < 0) break;
            *responseBuffer++ = static_cast<char>(c);
            count++;
        }

        // ReSharper disable once CppAssignedValueIsNeverUsed
        *responseBuffer++ = '\0';
        return _tcpStream.IsAvailable() ? InProgress : Completed;
    }

    size_t HttpTerminal::SendBody(const char* payload)
    {
        return _tcpStream.Transmit(payload);
    }

    size_t HttpTerminal::SendEmptyLine()
    {
        return _tcpStream.Transmit(_emptyLine);
    }

    void HttpTerminal::CloseConnection()
    {
        _tcpStream.Stop();
    }

    int HttpTerminal::TryExtractHttpStatusCode(char* responseBuffer, const size_t lengthOfResponseBuffer)
    {
        auto inStatus = false;
        char statusCode[4]{};
        auto j = 0;
        auto code = -1;

        for (size_t i = 0; i < lengthOfResponseBuffer; i++)
        {
            const auto c = responseBuffer[i];

            // Every HTTP status line begins with a H.
            if (i == 0 && (c != 'h' && c != 'H'))
            {
                return -1;
            }

            // End of line is also the end of the status line.
            if (c == '\r')
            {
                break;
            }

            // The first SP separates the status code from the HTTP version string.
            if (c == ' ' && !inStatus)
            {
                inStatus = true;
                continue;
            }

            if (inStatus && j < 3)
            {
                if (isdigit(c))
                {
                    statusCode[j] = c;
                    j++;
                }
                else // Sequence of three digits interrupted.
                {
                    break;
                }
            }

            if (j == 3)
            {
                statusCode[j] = '\0';
                code = atoi(statusCode);  // NOLINT(cert-err34-c)
                break;
            }
        }

        return code;
    }
}
