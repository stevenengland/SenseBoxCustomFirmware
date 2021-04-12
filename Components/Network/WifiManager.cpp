#include "WifiManager.h"

namespace Network
{
    namespace Wifi
    {
        void WifiManager::Connect()
        {
            _connector.Connect(_ssid, _password);
        }

        void WifiManager::Disconnect()
        {
            _connector.Disconnect();
        }

        void WifiManager::Reconnect()
        {
            _connector.Disconnect();
            _connector.Connect(_ssid, _password);
        }

        bool WifiManager::IsConnected()
        {
            return _connector.IsConnected();
        }
    }
}
