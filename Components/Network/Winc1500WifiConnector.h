#pragma once
#include "IWifiConnector.h"

namespace Network
{
    namespace Wifi
    {
        class Winc1500WifiConnector final : public IWifiConnector
        {
        public:
            void Connect(const char* ssid, const char* password) override;
            void Disconnect() override;
            bool IsConnected() override;
        };
    }
}
