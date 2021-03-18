#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "AnalogPortReaderMock.hpp"
#include "DfRobotSen0232.h"
#include "gmock/gmock-actions.h"
#include "gmock/gmock-matchers.h"

using namespace testing;

namespace SoundLevelMeterTests
{
    TEST(calculator_test, add_WhenPositiveArguments_WillReturnCorrectSum)
    {
        const auto expectedResult = 52;
        EXPECT_EQ(52, expectedResult);
    }

    TEST(DfRobotSen0232Should, ReadSensorValue)
    {
        // Arrange
        Connectivity::AnalogPorts::AnalogPortReaderMock mock;
        ON_CALL(mock, ReadVoltageFromPin(_)).WillByDefault(Return(6206.0606f));
        SoundLevelMeter::DfRobotSen0232 slm{ mock, 1 };

        // Act
        const auto dbValue = slm.ReadValue();

        // Assert
        ASSERT_NEAR(dbValue, 1000, 0.01);
    }
}
