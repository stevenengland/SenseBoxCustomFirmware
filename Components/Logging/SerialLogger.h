#pragma once

#include <cstdio>
#include <cstring>
#include <stdarg.h>
#include "Arduino.h"
#include "ILogger.h"
#include "LogLevel.h"

namespace Logging
{
    class SerialLogger final : public ILogger
    {
    public:
        explicit SerialLogger(const int logLevel)
            :
            _logLevel(logLevel)
        {
            Serial.begin(115200);
        }
        void Fatal(const char* format, ...) override;
        void Error(const char* format, ...) override;
        void Warning(const char* format, ...) override;
        void Notice(const char* format, ...) override;
        void Trace(const char* format, ...) override;
        void Verbose(const char* format, ...) override;
    private:
        int _logLevel = 0;

        void Log(const char* format, int logLevel, const char* prefix, va_list argumentPointer);
        void StreamPrintProgramMemory(Print& out, PGM_P format, ...)
        {
           va_list argumentPointer;
           va_start(argumentPointer, format);
           StreamPrintProgramMemory(out, format, argumentPointer);
           va_end(argumentPointer);
        }
        void StreamPrintProgramMemory(Print& out, PGM_P format, va_list argumentPointer)
        {
           // program memory version of printf - copy of format string and result share a buffer
           // so as to avoid too much memory use
           char formatString[128];
           strncpy_P(formatString, format, sizeof(formatString)); // copy in from program mem
           // null terminate - leave last char since we might need it in worst case for result's \0
           formatString[sizeof(formatString) - 2] = '\0';
           auto* ptr = &formatString[strlen(formatString) + 1]; // our result buffer...
           vsnprintf(ptr, sizeof(formatString) - 1 - strlen(formatString), formatString, argumentPointer);
           formatString[sizeof(formatString) - 1] = '\0';
           out.print(ptr);
        }
    };
}
