#include <gtest.h>
#include <gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "DfRobotSen0232.h"
#include <gmock-actions.h>
#include <gmock-matchers.h>

using namespace testing;

namespace SoundLevelMeterTests
{
    TEST(DfRobotSen0232Should, ReadSensorValue)
    {
        // Arrange
        Peripherals::AnalogPortReaderMock mock;
        ON_CALL(mock, ReadVoltageFromPin(_)).WillByDefault(Return(6206.0606f));
        Sensor::DfRobotSen0232 slm{ mock, 1 };

        // Act
        const auto dbValue = slm.ReadValue();

        // Assert
        ASSERT_NEAR(dbValue, 1000, 0.01);
    }
}
