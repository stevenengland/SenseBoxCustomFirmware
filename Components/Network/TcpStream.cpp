#include "TcpStream.h"

namespace Network
{
    bool TcpStream::Connect(const char* host, uint16_t port, const bool useSsl)
    {
        if (useSsl)
        {
            return _client.connectSSL(host, port);
        }

        return _client.connect(host, port);
    }

    bool TcpStream::IsConnected()
    {
        return _client.connected();
    }

    bool TcpStream::IsAvailable()
    {
        return _client.available();
    }

    int TcpStream::Receive()
    {
        return _client.read();
    }

    int TcpStream::Receive(uint8_t* buf, size_t size)
    {
        return _client.read(buf, size);
    }

    int TcpStream::Peek()
    {
        return _client.peek();
    }

    void TcpStream::Flush()
    {
        _client.flush();
    }

    void TcpStream::Stop()
    {
        _client.stop();
    }
    size_t TcpStream::Transmit(char* text)
    {
        return _client.print(text);
    }
}
