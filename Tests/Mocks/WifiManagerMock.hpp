#pragma once

#include <gmock/gmock.h>
#include "IWifiManager.h"

using namespace testing;

namespace Network
{
    namespace Wifi
    {
        class WifiManagerMock final : public IWifiManager
        {
        public:
            MOCK_METHOD(void, Connect, (), (override));
            MOCK_METHOD(void, Disconnect, (), (override));
            MOCK_METHOD(void, Reconnect, (), (override));
            MOCK_METHOD(bool, IsConnected, (), (override));
        };
    }
}
