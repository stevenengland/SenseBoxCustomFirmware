#pragma once

#include <gmock/gmock.h>
#include "WifiConnector.h"

using namespace testing;

namespace Connectivity
{
    namespace Wifi
    {
        class WifiConnectorMock final : public WifiConnector
        {
        public:
            MOCK_METHOD(void, Connect, (const char* ssid, const char* password), (override));
            MOCK_METHOD(void, Disconnect, (), (override));
            MOCK_METHOD(bool, IsConnected, (), (override));
        };
    }
}
