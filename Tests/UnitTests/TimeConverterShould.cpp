#include "gtest.h"
#include "TimeConverter.h"

namespace TimeTests
{
    class StandardTimeConverterShould :public ::testing::TestWithParam<std::tuple<std::string, int>> {
    protected:
        Time::TimeConverter _converter;
    };

    TEST_P(StandardTimeConverterShould, ReturnCorrectUtcTime) {
        std::string expected = std::get<0>(GetParam());
        int epoch = std::get<1>(GetParam());
        char strBuffer[35]{};
        _converter.GetUtcTime(epoch, strBuffer);
        ASSERT_EQ(expected, strBuffer);
    }

    INSTANTIATE_TEST_SUITE_P(
        StandardTimeConverterTests,
        StandardTimeConverterShould,
        ::testing::Values(
                std::make_tuple("2021-03-21T20:00:00Z", 1616356800),
                std::make_tuple("2021-03-21T20:00:15Z", 1616356815)));
}
