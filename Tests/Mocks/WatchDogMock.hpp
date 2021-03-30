#pragma once

#include <gmock/gmock.h>
#include "IWatchDog.h"

using namespace testing;

namespace Time
{
    class WatchDogMock final : public IWatchDog
    {
    public:
        MOCK_METHOD(int, Enable, (int milliseconds), (override));
        MOCK_METHOD(void, Disable, (), (override));
        MOCK_METHOD(void, Reset, (), (override));
    };
}
