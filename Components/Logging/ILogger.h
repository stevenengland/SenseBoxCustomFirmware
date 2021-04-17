#pragma once

namespace Logging
{
    class ILogger
    {
    public:
        virtual ~ILogger() = default;

        virtual void Begin() = 0;

        virtual void Fatal(const char* format, ...) = 0;
        virtual void Error(const char* format, ...) = 0;
        virtual void Warning(const char* format, ...) = 0;
        virtual void Notice(const char* format, ...) = 0;
        virtual void Trace(const char* format, ...) = 0;
        virtual void Verbose(const char* format, ...) = 0;
        virtual void FatalP(const char* format, ...) = 0;
        virtual void ErrorP(const char* format, ...) = 0;
        virtual void WarningP(const char* format, ...) = 0;
        virtual void NoticeP(const char* format, ...) = 0;
        virtual void TraceP(const char* format, ...) = 0;
        virtual void VerboseP(const char* format, ...) = 0;
    };
}
