#pragma once

#include "WifiConnector.h"

namespace Connectivity
{
    namespace Wifi
    {
        class WifiManager
        {
        public:
            WifiManager(
                WifiConnector& connector,
                const char* ssid,
                const char* password
            );
            void Connect() const;
            void Disconnect() const;
            void Reconnect() const;
            bool IsConnected() const;
        private:
            WifiConnector& _connector;
            const char* _ssid;
            const char* _password;
        };
    }
}
