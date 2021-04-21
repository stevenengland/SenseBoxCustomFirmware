#pragma once

#include <stddef.h>
#include <stdint.h>

namespace Network
{
    class ITcpStream
    {
    public:
        virtual ~ITcpStream() = default;

        virtual bool Connect(const char* host, uint16_t port, bool useSsl = true) = 0;
        virtual bool IsConnected() = 0;
        virtual bool IsAvailable() = 0;
        virtual int Receive() = 0;
        virtual int Receive(uint8_t* buf, size_t size) = 0;
        virtual int Peek() = 0;
        virtual void Flush() = 0;
        virtual void Stop() = 0;
        virtual size_t Transmit(char* text) = 0;
    };
}
