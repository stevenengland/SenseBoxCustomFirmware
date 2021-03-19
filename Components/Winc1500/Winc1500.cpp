#include "WiFi101.h"
#include <SPI.h>
#include <driver/source/nmasic.h>
#include "senseBoxIO.h"
#include "Arduino.h"
#include "Winc1500.h"


namespace Connectivity
{
    namespace Wifi
    {
        void Winc1500::Connect(const char ssid[], const char password[])
        {
            WiFi.begin(ssid, password);
        }

        void Winc1500::Disconnect()
        {
            WiFi.disconnect();
        }

        bool Winc1500::IsConnected()
        {
            return (WiFi.status() == WL_CONNECTED);
        }
    }
}