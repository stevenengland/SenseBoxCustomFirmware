#pragma once

#include <gmock.h>

#include "../../Components/Network/ITcpStream.h"

namespace Network
{
    class TcpStreamMock final : public Network::ITcpStream
    {
    public:
        MOCK_METHOD(bool, TryConnect, (const char* host, uint16_t port, bool useSsl), (override));
        MOCK_METHOD(bool, IsConnected, (), (override));
        MOCK_METHOD(bool, IsAvailable, (), (override));
        MOCK_METHOD(int, Receive, (), (override));
        MOCK_METHOD(int, Receive, (uint8_t* buf, size_t size), (override));
        MOCK_METHOD(int, Peek, (), (override));
        MOCK_METHOD(void, Flush, (), (override));
        MOCK_METHOD(void, Stop, (), (override));
        MOCK_METHOD(size_t, Transmit, (const char* text), (override));
    };
}
