#pragma once
#include "WifiConnector.h"

namespace Connectivity
{
    namespace Wifi
    {
        class Winc1500 final : public WifiConnector
        {
        public:
            void Connect(const char* ssid, const char* password) override;
            void Disconnect() override;
            bool IsConnected() override;
        };
    }
}
