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
    };
}
