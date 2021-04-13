#include "Arduino.h"
#include "SerialLogger.h"

namespace Logging
{
    void SerialLogger::Fatal(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelFatal, "[F]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Error(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelError, "[E]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Warning(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelWarning, "[W]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Notice(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelNotice, "[N]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Trace(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelTrace, "[T]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Verbose(const char* format, ...)
    {
        va_list argumentPointer;
        va_start(argumentPointer, format);
        Log(format, LogLevelVerbose, "[V]", argumentPointer);
        va_end(argumentPointer);
    }

    void SerialLogger::Log(const char* format, int logLevel, const char* prefix, va_list argumentPointer)
    {
        if (logLevel > _logLevel)
        {
            return;
        }
        StreamPrintProgramMemory(Serial, PSTR("%s - "), prefix);
        StreamPrintProgramMemory(Serial, PSTR(format), argumentPointer);
    }

}
