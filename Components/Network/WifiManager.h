#pragma once

#include "IWifiConnector.h"

namespace Network
{
    namespace Wifi
    {
        class WifiManager
        {
        public:
            WifiManager(
                IWifiConnector& connector,
                const char* ssid,
                const char* password
            );
            void Connect() const;
            void Disconnect() const;
            void Reconnect() const;
            bool IsConnected() const;
        private:
            IWifiConnector& _connector;
            const char* _ssid;
            const char* _password;
        };
    }
}
