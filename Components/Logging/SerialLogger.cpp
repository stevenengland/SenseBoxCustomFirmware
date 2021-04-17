#include "Arduino.h"
#include "SerialLogger.h"
#include "LogLevel.h"
#include <stdarg.h>

namespace Logging
{
    void SerialLogger::Begin()
    {
        Serial.begin(115200);
    }

    void SerialLogger::FatalP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::ErrorP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::WarningP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::NoticeP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::TraceP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::VerboseP(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, true, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Fatal(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Error(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Warning(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Notice(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Trace(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Verbose(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, false, argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Log(const char* format, const int logLevel, const bool printPrefix, va_list argumentPointer)
    {
        if (logLevel > _logLevel)
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

            StreamPrintProgramMemory(Serial, PSTR("%s - "), prefix);
        }

        StreamPrintProgramMemory(Serial, PSTR(format), argumentPointer);
    }

}
