#pragma once

namespace Peripherals
{
    class ISenseBoxIoMapper
    {
    public:
        virtual ~ISenseBoxIoMapper() = default;

        virtual void PowerAll() = 0;
    };
}
