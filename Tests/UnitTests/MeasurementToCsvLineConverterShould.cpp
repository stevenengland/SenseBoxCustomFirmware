#include "../../Components/Measurement/MeasurementToCsvLineConverter.h"
#include "../googletest-release-1.10.0/googletest/include/gtest/gtest.h"
#include "../Mocks/TimeConverterMock.hpp"

using namespace testing;

namespace MeasurementTests
{
    class MeasurementToCsvLineConverterShould : public Test
    {
    protected:
        Time::TimeConverterMock _timeConverterMock;
        Measurement::MeasurementToCsvLineConverter _converter{ _timeConverterMock };
    };

    TEST_F(MeasurementToCsvLineConverterShould, ReturnFormattedString_AfterConversion)
    {
        char *time = "2021-03-21T20:00:00Z";
        ON_CALL(_timeConverterMock, GetUtcTime(_,_)).WillByDefault(SetArrayArgument<1>(time, time + strlen(time) + 1));
        Measurement::Measurement measurement{ "FAKE0e9537bfd7001b507f01", 199.1f, 1616356800 };
        char buffer[100]{};
        const auto length = _converter.Convert(measurement, buffer);

        ASSERT_EQ(length, 56);
        ASSERT_STREQ(buffer, "FAKE0e9537bfd7001b507f01,   199.10,2021-03-21T20:00:00Z\n");
    }
}