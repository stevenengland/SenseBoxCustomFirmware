/*
This example creates a client object that connects and transfers
data using always SSL.

It is compatible with the methods normally related to plain
connections, like client.connect(host, port).

Written by Arturo Guadalupi
last revision November 2015

*/

#include <SPI.h>
#include <WiFi101.h>

#include "TcpStream.h"

#include "arduino_secrets.h" 
///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char Ssid[] = SECRET_SSID;        // your network SSID (name)
char Pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int KeyIndex = 0;            // your network key Index number (needed only for WEP)

int Status = WL_IDLE_STATUS;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
const char HostName[] PROGMEM = "www.google.com";    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
Network::TcpStream TcpClient;

// ReSharper disable once CppInconsistentNaming
void setup() {
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi 101 Shield not present");
        // don't continue:
        while (true);
    }

    // attempt to connect to WiFi network:
    while (Status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(Ssid);
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        Status = WiFi.begin(Ssid, Pass);

        // wait 10 seconds for connection:
        delay(10000);
    }
    Serial.println("Connected to WiFi");
    PrintWiFiStatus();

    Serial.println("\nStarting connection to server...");
    Serial.print("Availability before connection: ");
    Serial.println(TcpClient.IsAvailable());
    // if you get a connection, report back via serial:
    if (TcpClient.TryConnect(HostName, 443)) 
    {
        Serial.println("connected to server");
        Serial.print("Availability after establishing connection: ");
        Serial.println(TcpClient.IsAvailable());
        // Make a HTTP request:
        TcpClient.Transmit("GET /search?q=arduino HTTP/1.1\n");
        TcpClient.Transmit("Host: www.google.com\n");
        TcpClient.Transmit("Connection: close\n");
        TcpClient.Transmit("\n");
        Serial.print("Availability after transmission of request: ");
        Serial.println(TcpClient.IsAvailable());
        Serial.println(millis());
    }
}

bool firstMillisCall = true;
// ReSharper disable once CppInconsistentNaming
void loop() {
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (TcpClient.IsAvailable()) {
        if (firstMillisCall) // To show how many millis elapsed since the transmission until client became available.
        {
            Serial.println(millis());
            firstMillisCall = false;
        }

        char c = TcpClient.Receive();
        Serial.write(c);
    }

    // if the server's disconnected, stop the client:
    if (!TcpClient.IsConnected()) {
        Serial.println();
        Serial.println("disconnecting from server.");
        TcpClient.Stop();

        // do nothing forevermore:
        while (true);
    }
}


void PrintWiFiStatus() {
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi 101 Shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}