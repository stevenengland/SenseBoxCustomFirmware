#include "WifiManager.h"
#include "Winc1500.h"
#include "Arduino.h"
#include "senseBoxIO.h"
#include "arduino_secrets.h" 

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;
Connectivity::Wifi::Winc1500 wifiConnector;
Connectivity::Wifi::WifiManager wifiManager{wifiConnector, ssid, pass};

void setup()
{
    senseBoxIO.powerAll();
    
    // init serial library
    Serial.begin(9600);
    while(!Serial); // wait for serial monitor
    Serial.println("WINC1500");

        while (wifiManager.IsConnected() != true) 
        {
            Serial.print("Attempting to connect to WPA SSID: ");
            Serial.println(ssid);
            // Connect to WPA/WPA2 network:
            wifiManager.Connect();
            // wait 10 seconds for connection:
            delay(10000);
        }
        Serial.print("Connected.");   
}

void loop()
{
    delay(10000);
    if (wifiManager.IsConnected() == false)
    {
        while (wifiManager.IsConnected() == false) 
        {
            Serial.print("Attempting to reconnect to WPA SSID: ");
            Serial.println(ssid);
            // Connect to WPA/WPA2 network:
            wifiManager.Reconnect();
            // wait 10 seconds for connection:
            delay(10000);
        }
    }
}