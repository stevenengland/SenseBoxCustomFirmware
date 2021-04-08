#pragma once

#include <gmock/gmock.h>

#include "../../Components/Time/ITimeConverter.h"

namespace Time
{
    class TimeConverterMock final : public ITimeConverter
    {
    public:
        MOCK_METHOD(void, GetUtcTime, (time_t epochTime, char* utcTimeOutput), (override));
    };
}
