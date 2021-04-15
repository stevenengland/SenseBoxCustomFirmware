#include "Arduino.h"
#include "Winc1500TelnetLogger.h"

#include "LogLevel.h"

namespace Logging
{
    void Winc1500TelnetLogger::Begin()
    {
        if (!_server.available() && WiFi.status() == WL_CONNECTED)
        {
            _server.begin();
        }
    }

    void Winc1500TelnetLogger::Fatal(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, "[F]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Error(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, "[E]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Warning(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, "[W]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Notice(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, "[N]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Trace(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, "[T]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Verbose(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, "[V]", argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Log(const char* format, int logLevel, const char* prefix, va_list argumentPointer)
    {
        if (logLevel > _logLevel)
        {
            return;
        }

        _client = _server.available();
        if (!_client)
        {
            return;
        }

        StreamPrintProgramMemory(_server, PSTR("%s - "), prefix);
        StreamPrintProgramMemory(_server, PSTR(format), argumentPointer);
    }

}
