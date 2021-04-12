#pragma once

#include "IWifiConnector.h"
#include "IWifiManager.h"

namespace Network
{
    namespace Wifi
    {
        class WifiManager final : public IWifiManager
        {
        public:
            WifiManager(
                IWifiConnector& connector,
                const char* ssid,
                const char* password)
                    :
            _connector(connector),
            _ssid(ssid),
            _password(password)
            {
            }
            void Connect() override;
            void Disconnect() override;
            void Reconnect() override;
            bool IsConnected() override;
        private:
            IWifiConnector& _connector;
            const char* _ssid;
            const char* _password;
        };
    }
}
