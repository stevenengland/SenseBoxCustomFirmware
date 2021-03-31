#include "WifiManager.h"

namespace Network
{
    namespace Wifi
    {
        WifiManager::WifiManager(
            IWifiConnector& connector,
            const char* ssid,
            const char* password
            )
            :
        _connector{ connector },
        _ssid{ ssid },
        _password{ password }
        {
        }

        void WifiManager::Connect() const
        {
            _connector.Connect(_ssid, _password);
        }

        void WifiManager::Disconnect() const
        {
            _connector.Disconnect();
        }

        void WifiManager::Reconnect() const
        {
            _connector.Disconnect();
            _connector.Connect(_ssid, _password);
        }

        bool WifiManager::IsConnected() const
        {
            return _connector.IsConnected();
        }
    }
}
