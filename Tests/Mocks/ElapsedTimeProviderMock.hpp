#pragma once

#include <gmock/gmock.h>
#include "ElapsedTimeProvider.h"

namespace Time
{
    class ElapsedTimeProviderMock final : public ElapsedTimeProvider
    {
    public:
        MOCK_METHOD(unsigned long, ElapsedMilliseconds, (), (override));
        MOCK_METHOD(void, WaitSync, (int milliseconds), (override));
    };
}
