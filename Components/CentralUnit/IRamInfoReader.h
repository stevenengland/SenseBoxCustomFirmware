#pragma once

namespace CentralUnit
{
    class IRamInfoReader
    {
    public:
        virtual ~IRamInfoReader() = default;

        virtual int GetFreeRamSize() = 0;
    };
}
