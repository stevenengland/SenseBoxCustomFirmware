#pragma once

#include "ITcpStream.h"
#include "WiFiClient.h"

namespace Network
{
    class TcpStream final : public ITcpStream
    {
    public:
        bool TryConnect(const char* host, uint16_t port, bool useSsl = true) override;
        bool IsConnected() override;
        bool IsAvailable() override;
        int Receive() override;
        int Receive(uint8_t* buf, size_t size) override;
        int Peek() override;
        void Flush() override;
        void Stop() override;
        size_t Transmit(const char* text) override;
    private:
        WiFiClient _client{};
    };
}
