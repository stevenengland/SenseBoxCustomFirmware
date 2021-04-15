#pragma once

#include <gmock.h>
#include "ILogger.h"

namespace Logging
{
    // Variadic functions cannot really be mocked so here is more of a stub than a real mock.
    class LoggerMock final : public ILogger
    {
    public:
        void Fatal(const char* format, ...) override { printf(format); };
        void Error(const char* format, ...) override { printf(format); };
        void Warning(const char* format, ...) override { printf(format); };
        void Notice(const char* format, ...) override { printf(format); };
        void Trace(const char* format, ...) override { printf(format); };
        void Verbose(const char* format, ...) override { printf(format); };
        MOCK_METHOD(void, Begin, (), (override));
    };
}
