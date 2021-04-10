#pragma once

#include <gmock/gmock.h>
#include "ISenseBoxIoMapper.h"

namespace Peripherals
{
    class SenseBoxIoMapperMock final : public ISenseBoxIoMapper
    {
    public:
        MOCK_METHOD(void, PowerAll, (), (override));
    };
}
