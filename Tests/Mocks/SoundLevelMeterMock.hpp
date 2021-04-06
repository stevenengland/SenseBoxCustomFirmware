#pragma once

#include <gmock/gmock.h>
#include "ISoundLevelMeter.h"

namespace SoundLevelMeter
{
    class SoundLevelMeterMock final : public ISoundLevelMeter
    {
    public:
        MOCK_METHOD(float, ReadValue, (), (override));
    };
}
