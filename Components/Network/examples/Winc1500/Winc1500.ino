#include "WifiManager.h"
#include "Winc1500WifiConnector.h"
#include "Arduino.h"
#include "senseBoxIO.h"
#include "arduino_secrets.h" 

char Ssid[] = SECRET_SSID;
char Pass[] = SECRET_PASS;
Network::Wifi::Winc1500WifiConnector wifiConnector;
Network::Wifi::WifiManager wifiManager{wifiConnector, Ssid, Pass};

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
            Serial.println(Ssid);
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
            Serial.println(Ssid);
            // Connect to WPA/WPA2 network:
            wifiManager.Reconnect();
            // wait 10 seconds for connection:
            delay(10000);
        }
    }
}