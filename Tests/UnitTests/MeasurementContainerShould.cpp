#include <gtest.h>
#include <gmock.h>

#include "MeasurementContainer.h"
#include "Measurement.h"

using namespace testing;

namespace MeasurementContainerTests
{
    class MeasurementContainerShould : public Test
    {
    public:
        Measurement::MeasurementContainer container{ 100 };
    };

    TEST_F(MeasurementContainerShould, ReturnFalse_IfIndexOfSearchedMeasurementIsNegative)
    {
        Measurement::Measurement measurementToAdd;
        Measurement::Measurement measurementToGet;

        container.AddMeasurement(measurementToAdd);

        ASSERT_FALSE(container.GetMeasurement(-1, measurementToGet));
    }

    TEST_F(MeasurementContainerShould, ReturnFalse_IfContainerIsEmpty)
    {
        Measurement::Measurement measurement;

        ASSERT_FALSE(container.GetMeasurement(1, measurement));
    }

    TEST_F(MeasurementContainerShould, ReturnFalse_IfIndexOfSearchedMeasurementIsTooBig) 
    {
        Measurement::Measurement measurementToAdd;
        Measurement::Measurement measurementToGet;

        container.AddMeasurement(measurementToAdd);

        ASSERT_FALSE(container.GetMeasurement(2, measurementToGet));
    }

    TEST_F(MeasurementContainerShould, ReturnCountGt0_WhenMeasurementWasAdded) 
    {
        Measurement::Measurement measurement;

        container.AddMeasurement(measurement);

        ASSERT_EQ(1, container.Count());
    }

    TEST_F(MeasurementContainerShould, ReturnCountEq0_WhenMeasurementsWereCleared) 
    {
        Measurement::Measurement measurement;
        container.AddMeasurement(measurement);

        container.ClearMeasurements();

        ASSERT_EQ(0, container.Count());
    }

    TEST_F(MeasurementContainerShould, ReturnCountEqCapacity_WhenMoreMeasurementsAreAddedThanContainersCapacyity) 
    {
        for (size_t i = 0; i < 102; i++)
        {
            Measurement::Measurement measurement;
            container.AddMeasurement(measurement);
        }

        ASSERT_EQ(100, container.Count());
    }

}
