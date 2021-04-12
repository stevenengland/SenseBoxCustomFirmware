#pragma once

namespace Network
{
    namespace Wifi
    {
        class IWifiManager
        {
        public:
            virtual ~IWifiManager() = default;

            virtual void Connect() = 0;
            virtual void Disconnect() = 0;
            virtual void Reconnect() = 0;
            virtual bool IsConnected() = 0;
        };
    }
}
