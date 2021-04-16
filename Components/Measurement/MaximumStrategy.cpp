#include "MaximumStrategy.h"

namespace Measurement
{
    float MaximumStrategy::Aggregate(float nextValue)
    {
        if (_isFirstCall)
        {
            _isFirstCall = false;
            _currentAggregate = nextValue;
        }
        else
        {
            _currentAggregate = (_currentAggregate > nextValue) ? _currentAggregate : nextValue;
        }

        return _currentAggregate;
    }

    void MaximumStrategy::Reset()
    {
        _isFirstCall = true;
        _currentAggregate = 0;
    }
}
