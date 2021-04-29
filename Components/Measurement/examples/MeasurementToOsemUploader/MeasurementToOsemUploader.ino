#include <SPI.h>
#include <WiFi101.h>

#include "arduino_secrets.h"
#include "MeasurementContainer.h"
#include "MeasurementToCsvLineConverter.h"
#include "HttpTerminal.h"
#include "MeasurementToOsemUploader.h"
#include "TcpStream.h"
#include "ArduinoElapsedTimeProvider.h"
#include "TimeConverter.h"
#include "Measurement.h"
#include "Winc1500TimeProvider.h"
#include "TransmissionStatus.h"

char Ssid[] = SECRET_SSID;
char Pass[] = SECRET_PASS;

char BoxId[] = BOX_ID;
char AuthToken[] = AUTH_TOKEN;
char SensorId[] = SENSOR_ID;
char ServerHostName[] = "ingress.workshop.opensensemap.org"; // See values at workshop.opensensemap.org

int Status = WL_IDLE_STATUS;

Network::TcpStream TcpStream;
Time::ArduinoElapsedTimeProvider ElapsedTimeProvider;
Time::TimeConverter TimeConverter;
Time::Winc1500TimeProvider TimeProvider;
Network::HttpTerminal Terminal { TcpStream, ElapsedTimeProvider };
Measurement::MeasurementContainer Container{ 1000 };
Measurement::MeasurementToCsvLineConverter Converter { TimeConverter };
Measurement::MeasurementToOsemUploader Uploader
{
    Terminal,
    Converter,
    ServerHostName,
    443,
    BoxId,
    AuthToken
};

void SendDataToOsem()
{
    Serial.println("Building measurements...");
    auto time = TimeProvider.GetEpochTime();
    for (auto i = 0; i < 1000; i++)
    {
        Measurement::Measurement measurement{ SensorId, (i+1) % 7 + 0.1, time-- };
        Container.AddMeasurement(measurement);
    }

    Serial.println("Sending data...");
    auto uploadStatus = Uploader.TrySendUpload(Container);
    if (uploadStatus == Completed)
    {
        Serial.println("Data sent...");
        char buffer[100]{};
        auto proceedReading = true;
        while (proceedReading)
        {
            auto tStatus = Uploader.ReadUploadResponse(buffer, sizeof(buffer), 2000);
            Serial.println(tStatus);
            if (tStatus == InProgress || tStatus == Completed)
            {
                Serial.write(buffer);
                if (tStatus == Completed)
                {
                    proceedReading = false;
                }
            }
            else
            {
                proceedReading = false;
            }
        }
    }
    else
    {
        Serial.print("Data could not be sent... Status: ");
        Serial.println(uploadStatus);
    }
}

// ReSharper disable once CppInconsistentNaming
void setup()
{
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

    SendDataToOsem();
}

// ReSharper disable once CppInconsistentNaming
void loop()
{
    
}