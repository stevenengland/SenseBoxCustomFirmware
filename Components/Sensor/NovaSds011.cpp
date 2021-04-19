#include "NovaSds011.h"

#include <math.h>

namespace Sensor
{
    bool NovaSds011::Init()
    {
        _driver.Begin();
        return true;
    }

    float NovaSds011::ReadValue(const int phenomenonId)
    {
        if (phenomenonId > 1)
        {
            return NAN;
        }

        float p10, p25;
        bool error;
        _driver.Read(p25, p10, error);
        
        if (error)
        {
            return NAN;
        }
        else
        {
            switch (phenomenonId)
            {
                case 0:
                    return p25;
                case 1:
                    return p10;
                default:
                    return NAN;
            }
        }
    }

    SensorReads NovaSds011::ReadValues()
    {
        SensorReads reads{};
        float p10, p25;
        bool error;
        _driver.Read(p25, p10, error);
        if (error)
        {
            reads.Reads[0] = NAN;
            reads.Reads[1] = NAN;
        }
        else
        {
            reads.Reads[0] = p25;
            reads.Reads[1] = p10;
        }

        return reads;
    }

}
