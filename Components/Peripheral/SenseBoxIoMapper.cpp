#include "Arduino.h"
#include "senseBoxIO.h"
#include "SenseBoxIoMapper.h"

namespace Peripherals
{
    void SenseBoxIoMapper::PowerAll()
    {
        senseBoxIO.powerAll();
    }
}
