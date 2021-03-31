#pragma once

namespace Network
{
    namespace Wifi
    {
        class IWifiConnector
        {
        public:
            virtual ~IWifiConnector() = default;

            virtual void Connect(const char* ssid, const char* password) = 0;
            virtual void Disconnect() = 0;
            virtual bool IsConnected() = 0;
        };
    }
}