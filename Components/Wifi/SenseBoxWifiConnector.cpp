#include "senseBoxIO.h"
#include "WiFi101.h"
#include "WifiConnector.h"

void Connectivity::Wifi::WifiConnector::Connect(const char ssid[], const char password[])
{
    // WINC1500 (WiFi-Bee) in XBEE1 Socket
    senseBoxIO.powerXB1(false); // power off to reset WINC1500
    delay(250);
    senseBoxIO.powerXB1(true);  // power on
    delay(250);
    WiFi.begin(ssid, password);
}

void Connectivity::Wifi::WifiConnector::Disconnect()
{      
    WiFi.disconnect();
}

bool Connectivity::Wifi::WifiConnector::IsConnected()
{
    return (WiFi.status() == WL_CONNECTED);
}