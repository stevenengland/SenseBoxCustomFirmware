#pragma once

namespace Connectivity
{
    namespace Wifi
    {
        class WifiConnector
        {
        public:
            virtual ~WifiConnector() = default;

            virtual void Connect(const char* ssid, const char* password) = 0;
            virtual void Disconnect() = 0;
            virtual bool IsConnected() = 0;
        };
    }
}