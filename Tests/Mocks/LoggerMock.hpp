#pragma once

#include <gmock.h>
#include "ILogger.h"

namespace Logging
{
    // Variadic functions cannot really be mocked so here is more of a stub than a real mock.
    class LoggerMock final : public ILogger
    {
    public:
        void Fatal(const char* format, ...) override { format; };
        void Error(const char* format, ...) override { format; };
        void Warning(const char* format, ...) override { format; };
        void Notice(const char* format, ...) override { format; };
        void Trace(const char* format, ...) override { format; };
        void Verbose(const char* format, ...) override { format; };
        void FatalP(const char* format, ...) override { format; };
        void ErrorP(const char* format, ...) override { format; };
        void WarningP(const char* format, ...) override { format; };
        void NoticeP(const char* format, ...) override { format; };
        void TraceP(const char* format, ...) override { format; };
        void VerboseP(const char* format, ...) override { format; };
        MOCK_METHOD(void, Begin, (), (override));
    };
}
