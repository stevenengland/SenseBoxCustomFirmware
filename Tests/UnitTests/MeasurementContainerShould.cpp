#include <gtest.h>
#include <gmock.h>

#include "MeasurementContainer.h"
#include "Measurement.h"

using namespace testing;

namespace MeasurementContainerTests
{
    class MeasurementContainerShould : public Test
    {
    protected:
        Measurement::MeasurementContainer _container{ 100 };
    };

    TEST_F(MeasurementContainerShould, ReturnFalse_IfIndexOfSearchedMeasurementIsNegative)
    {
        Measurement::Measurement measurementToAdd;
        Measurement::Measurement measurementToGet;

        _container.AddMeasurement(measurementToAdd);

        ASSERT_FALSE(_container.GetMeasurement(-1, measurementToGet));
    }

    TEST_F(MeasurementContainerShould, ReturnFalse_IfContainerIsEmpty)
    {
        Measurement::Measurement measurement;

        ASSERT_FALSE(_container.GetMeasurement(1, measurement));
    }

    TEST_F(MeasurementContainerShould, ReturnFalse_IfIndexOfSearchedMeasurementIsTooBig) 
    {
        Measurement::Measurement measurementToAdd;
        Measurement::Measurement measurementToGet;

        _container.AddMeasurement(measurementToAdd);

        ASSERT_FALSE(_container.GetMeasurement(2, measurementToGet));
    }

    TEST_F(MeasurementContainerShould, ReturnCountGt0_WhenMeasurementWasAdded) 
    {
        Measurement::Measurement measurement;

        _container.AddMeasurement(measurement);

        ASSERT_EQ(1, _container.Count());
    }

    TEST_F(MeasurementContainerShould, ReturnCountEq0_WhenMeasurementsWereCleared) 
    {
        Measurement::Measurement measurement;
        _container.AddMeasurement(measurement);

        _container.ClearMeasurements();

        ASSERT_EQ(0, _container.Count());
    }

    TEST_F(MeasurementContainerShould, ReturnCountEqCapacity_WhenMoreMeasurementsAreAddedThanContainersCapacyity) 
    {
        for (size_t i = 0; i < 102; i++)
        {
            Measurement::Measurement measurement;
            _container.AddMeasurement(measurement);
        }

        ASSERT_EQ(100, _container.Count());
    }

}
