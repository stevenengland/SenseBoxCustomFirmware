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
            // WINC1500 (WiFi-Bee) in XBEE1 Socket
            senseBoxIO.powerXB1(false); // power off to reset WINC1500
            delay(250);
            senseBoxIO.powerXB1(true);  // power on
            delay(250);
            
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