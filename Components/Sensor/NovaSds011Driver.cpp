#include "NovaSds011Driver.h"

#include <cstdint>

static constexpr uint8_t SleepCommand[19] = {
0xAA, 0xB4, 0x06, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	0x00, 0x00, 0x00, 0xFF,	0xFF, 0x05, 0xAB
};
static constexpr uint8_t WakeupCommand[19] = {
    0xAA, 0xB4, 0x06, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x06, 0xAB
};

namespace Sensor
{
    void NovaSds011Driver::Begin()
    {
        if (!_needsInit)
        {
            return;
        }
        _uart.begin(9600);
        _needsInit = false;
    }

    void NovaSds011Driver::Read(float& p25, float& p10, bool& error)
    {
        uint8_t attempt = 0;
        float pm10, pm25;
        while (attempt < 5) {
            error = _sds.read(&pm25, &pm10);
            if (!error) {
                p25 = pm25;
                p10 = pm10;
                break;
            }
            attempt++;
        }
    }

    void NovaSds011Driver::Sleep()
    {
        for (uint8_t i = 0; i < 19; i++) {
            _uart.write(SleepCommand[i]);
        }
        _uart.flush();
        while (_uart.available() > 0) {
            _uart.read();
        }
    }

    void NovaSds011Driver::Wakeup()
    {
        for (uint8_t i = 0; i < 19; i++) {
            _uart.write(WakeupCommand[i]);
        }
        _uart.flush();
        while (_uart.available() > 0) {
            _uart.read();
        }
    }
}
