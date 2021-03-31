#pragma once

#include <gmock/gmock.h>
#include "IWifiConnector.h"

using namespace testing;

namespace Network
{
    namespace Wifi
    {
        class WifiConnectorMock final : public IWifiConnector
        {
        public:
            MOCK_METHOD(void, Connect, (const char* ssid, const char* password), (override));
            MOCK_METHOD(void, Disconnect, (), (override));
            MOCK_METHOD(bool, IsConnected, (), (override));
        };
    }
}
