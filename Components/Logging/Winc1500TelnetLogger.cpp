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

    void Winc1500TelnetLogger::FatalP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::ErrorP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::WarningP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::NoticeP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::TraceP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::VerboseP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, true, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Fatal(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Error(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Warning(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Notice(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Trace(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Verbose(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, false, argumentPointer);
        va_end(argumentPointer);
    }

    void Winc1500TelnetLogger::Log(const char* format, const int logLevel, const bool printPrefix, va_list argumentPointer)
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

        if (printPrefix)
        {
            char* prefix;

            switch (logLevel)
            {
            case LogLevelFatal:
                prefix = "[F]";
                break;
            case LogLevelError:
                prefix = "[E]";
                break;
            case LogLevelWarning:
                prefix = "[W]";
                break;
            case LogLevelNotice:
                prefix = "[N]";
                break;
            case LogLevelTrace:
                prefix = "[T]";
                break;
            case LogLevelVerbose:
                prefix = "[V]";
                break;
            default:
                break;;
            }

            StreamPrintProgramMemory(_server, PSTR("%s - "), prefix);
        }

        StreamPrintProgramMemory(_server, PSTR(format), argumentPointer);
    }

}
