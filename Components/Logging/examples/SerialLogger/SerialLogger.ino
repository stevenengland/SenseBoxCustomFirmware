#include "SerialLogger.h"
#include "LogLevel.h"

Logging::SerialLogger Logger{LogLevelWarning};

// ReSharper disable once CppInconsistentNaming
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }

    Logger.Fatal("That went wrong: %d - %s\n", 25, "specific error");
    Logger.Warning("Warning: Rain is coming.\n");

    Logger.Notice("Should not be printed out...");
}

// ReSharper disable once CppInconsistentNaming
void loop() {
    // put your main code here, to run repeatedly:

}
