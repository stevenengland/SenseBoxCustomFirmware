#include "WiFi101.h"
#include <SPI.h>
#include <driver/source/nmasic.h>
#include "senseBoxIO.h"
#include "Arduino.h"
#include "Winc1500WifiConnector.h"


namespace Network
{
    namespace Wifi
    {
        void Winc1500WifiConnector::Connect(const char ssid[], const char password[])
        {
            WiFi.begin(ssid, password);
        }

        void Winc1500WifiConnector::Disconnect()
        {
            WiFi.disconnect();
        }

        bool Winc1500WifiConnector::IsConnected()
        {
            return (WiFi.status() == WL_CONNECTED);
        }
    }
}