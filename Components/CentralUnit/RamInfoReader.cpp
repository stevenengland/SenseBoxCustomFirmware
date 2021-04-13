#include "MemoryManagement.h"
#include "RamInfoReader.h"

namespace CentralUnit
{
    int RamInfoReader::GetFreeRamSize()
    {
        char top = 0;
#ifdef __arm__
        return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)  // NOLINT(clang-diagnostic-undef)
        return &top - __brkval;
#else  // __arm__
        return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
    }
}
