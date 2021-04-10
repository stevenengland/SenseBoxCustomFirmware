#pragma once

#include <gmock/gmock.h>
#include "ITimeProvider.h"

using namespace testing;

namespace Time
{
    class TimeProviderMock final : public ITimeProvider
    {
    public:
        MOCK_METHOD(time_t, GetEpochTime, (), (override));
    };
}
