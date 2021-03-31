#pragma once

#include <gmock/gmock.h>
#include "IElapsedTimeProvider.h"

namespace Time
{
    class ElapsedTimeProviderMock final : public IElapsedTimeProvider
    {
    public:
        MOCK_METHOD(unsigned long, ElapsedMilliseconds, (), (override));
        MOCK_METHOD(void, WaitSync, (int milliseconds), (override));
    };
}
