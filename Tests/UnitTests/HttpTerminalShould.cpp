#include <gtest/gtest.h>
#include "HttpTerminal.h"
#include "TcpStreamMock.hpp"
#include "ElapsedTimeProviderMock.hpp"

using namespace testing;

namespace NetworkTests
{
    class HttpTerminalShould : public Test 
    {
    protected:
        Network::TcpStreamMock _tcpStreamMock;
        Time::ElapsedTimeProviderMock _elapsedTimeProviderMock;
        Network::HttpTerminal _terminal { _tcpStreamMock, _elapsedTimeProviderMock };
    };

    class GivenStatusCodes_HttpTerminalShould : public HttpTerminalShould, public WithParamInterface<std::tuple<std::string, int>>
    {
    };

    TEST_F(HttpTerminalShould, CloseConnectionCorrectly)
    {
        EXPECT_CALL(_tcpStreamMock, Stop()).Times(1);

        _terminal.CloseConnection();
    }

    TEST_F(HttpTerminalShould, ReturnTrue_IfConnectionIsSuccessful)
    {
        EXPECT_CALL(_tcpStreamMock, TryConnect(_, _, _)).WillOnce(Return(true));

        ASSERT_TRUE(_terminal.TryConnect("", 80, false));
    }

    TEST_F(HttpTerminalShould, ReturnFalse_IfConnectionFails)
    {
        EXPECT_CALL(_tcpStreamMock, TryConnect(_, _, _)).WillOnce(Return(false));

        ASSERT_FALSE(_terminal.TryConnect("", 80, false));
    }

    TEST_F(HttpTerminalShould, CleanUp_IfConnectionFails)
    {
        EXPECT_CALL(_tcpStreamMock, TryConnect(_, _, _)).WillOnce(Return(false));
        EXPECT_CALL(_tcpStreamMock, Stop()).Times(1);

        ASSERT_FALSE(_terminal.TryConnect("", 80, false));
    }

    TEST_F(HttpTerminalShould, SendCorrectEmptyLine)
    {
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("\r\n"))).WillOnce(Return(5));;

        size_t requestSize = _terminal.SendEmptyLine();

        ASSERT_EQ((size_t)5, requestSize);
    }

    TEST_F(HttpTerminalShould, SendCorrectBody)
    {
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("payload of some kind"))).WillOnce(Return(5));

        size_t requestSize = _terminal.SendBody("payload of some kind");

        ASSERT_EQ((size_t)5, requestSize);
    }

    TEST_F(HttpTerminalShould, SendCorrectRequestLine)
    {
        InSequence s;
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("POST"))).WillOnce(Return(4));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq(" "))).WillOnce(Return(1));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("localhost:80"))).WillOnce(Return(12));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq(" "))).WillOnce(Return(1));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("HTTP/1.1"))).WillOnce(Return(8));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("\r\n"))).WillOnce(Return(2));

        size_t requestSize = _terminal.SendRequestLine("POST", "localhost:80", "HTTP/1.1");

        ASSERT_EQ((size_t)28, requestSize);
    }

    TEST_F(HttpTerminalShould, SendCorrectHeader)
    {
        InSequence s;
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("Connection"))).WillOnce(Return(10));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq(": "))).WillOnce(Return(2));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("close"))).WillOnce(Return(5));
        EXPECT_CALL(_tcpStreamMock, Transmit(StrEq("\r\n"))).WillOnce(Return(2));

        size_t requestSize = _terminal.SendHeader("Connection", "close");

        ASSERT_EQ((size_t)19, requestSize);
    }

    TEST_F(HttpTerminalShould, ReturnZero_IfReadingResponseTimesOut)
    {
        EXPECT_CALL(_tcpStreamMock, IsAvailable()).WillRepeatedly(Return(false));
        EXPECT_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(1000)) // start
            .WillOnce(Return(2001)); // elapsed since start
        char buffer[10]{};

        auto tStatus = _terminal.ReadResponse(buffer, sizeof(buffer), 1000);

        ASSERT_EQ(Timeout, tStatus);
    }

    TEST_F(HttpTerminalShould, CloseConnection_IfReadingResponseTimesOut)
    {
        EXPECT_CALL(_tcpStreamMock, IsAvailable()).WillRepeatedly(Return(false));
        EXPECT_CALL(_tcpStreamMock, Stop()).Times(1);
        EXPECT_CALL(_elapsedTimeProviderMock, ElapsedMilliseconds())
            .WillOnce(Return(1000)) // start
            .WillOnce(Return(2001)); // elapsed since start
        char buffer[10]{};

        _terminal.ReadResponse(buffer, sizeof(buffer), 1000);
    }

    TEST_F(HttpTerminalShould, ReturnCompletedTransmission_IfResponseSizeIsSmallerThanResponseBuffer)
    {
        //InSequence s;
        //EXPECT_CALL(_tcpStreamMock, IsConnected()).WillOnce(Return(true));
        //EXPECT_CALL(_tcpStreamMock, IsAvailable()).WillOnce(Return(true));
        //EXPECT_CALL(_tcpStreamMock, Receive()).WillOnce(Return(50));
        //EXPECT_CALL(_tcpStreamMock, IsConnected()).WillOnce(Return(true));
        //EXPECT_CALL(_tcpStreamMock, IsAvailable()).WillOnce(Return(true));
        //EXPECT_CALL(_tcpStreamMock, Receive()).WillOnce(Return(51));
        //EXPECT_CALL(_tcpStreamMock, IsConnected()).WillOnce(Return(true));
        //EXPECT_CALL(_tcpStreamMock, IsAvailable()).WillOnce(Return(false));

        EXPECT_CALL(_tcpStreamMock, IsAvailable())
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(false))
            .WillOnce(Return(false));
        EXPECT_CALL(_tcpStreamMock, Receive())
            .WillOnce(Return(50))
            .WillOnce(Return(51));
        char buffer[10]{};

        auto tStatus = _terminal.ReadResponse(buffer, sizeof(buffer));

        ASSERT_EQ((size_t)2, strlen(buffer));
        ASSERT_EQ(Completed, tStatus);
        ASSERT_STREQ("23", buffer);
    }

    TEST_F(HttpTerminalShould, FillResponseBufferTwice_IfResponseSizeIsGreaterThanResponseBuffer)
    {
        EXPECT_CALL(_tcpStreamMock, IsAvailable())
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))

            .WillOnce(Return(true))
            .WillOnce(Return(false))
            .WillOnce(Return(false));
        EXPECT_CALL(_tcpStreamMock, Receive())
            .WillOnce(Return(50))
            .WillOnce(Return(51))
            .WillOnce(Return(52));

        char buffer[3]{};

        auto tStatus1 = _terminal.ReadResponse(buffer, sizeof(buffer));
        
        ASSERT_EQ((size_t)2, strlen(buffer));
        ASSERT_EQ(InProgress, tStatus1);
        ASSERT_STREQ("23", buffer);

        auto tStatus2 = _terminal.ReadResponse(buffer, sizeof(buffer));

        ASSERT_EQ((size_t)1, strlen(buffer));
        ASSERT_EQ(Completed, tStatus2);
        ASSERT_STREQ("4", buffer);
    }

    TEST_F(HttpTerminalShould, FillResponseBufferOnce_IfResponseSizeIsEqualToResponseBuffer)
    {
        EXPECT_CALL(_tcpStreamMock, IsAvailable())
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(true))
            .WillOnce(Return(false))
            .WillOnce(Return(false))
            .WillOnce(Return(true))
            .WillOnce(Return(false))
            .WillOnce(Return(false));
        EXPECT_CALL(_tcpStreamMock, Receive())
            .WillOnce(Return(50))
            .WillOnce(Return(51))
            .WillOnce(Return(52));
        char buffer[4]{};

        auto tStatus1 = _terminal.ReadResponse(buffer, sizeof(buffer));
        
        ASSERT_EQ((size_t)3, strlen(buffer));
        ASSERT_EQ(Completed, tStatus1);
        ASSERT_STREQ("234", buffer);

        auto tStatus2 = _terminal.ReadResponse(buffer, sizeof(buffer));

        ASSERT_EQ((size_t)0, strlen(buffer));
        ASSERT_EQ(Completed, tStatus2);
        ASSERT_STREQ("", buffer);
    }

    TEST_P(GivenStatusCodes_HttpTerminalShould, ReturnCorrectStatusCode) 
    {
        std::string input = std::get<0>(GetParam());
        char* cstr = &input[0];
        int expected = std::get<1>(GetParam());

        auto statusCode = _terminal.TryExtractHttpStatusCode(cstr, input.length() + 1);

        ASSERT_EQ(statusCode, expected);
    }

    INSTANTIATE_TEST_SUITE_P(
        HttpTerminalTests,
        GivenStatusCodes_HttpTerminalShould,
        ::testing::Values(
                std::make_tuple("HTTP/1.1 200 OK\r\n", 200), // Normal response
                std::make_tuple("HTTP/1.1 200 OK", 200), // No end of line
                std::make_tuple("HTTP/1.1 2000 OK", 200), // More than three digits
                std::make_tuple("http/1.1 200 OK", 200), // Small h
                std::make_tuple("xttp/1.1 200 OK", -1), // Wrong first character
                std::make_tuple("HTTP/1.1  200 OK", -1), // Two SP
                std::make_tuple("HTTP/1.1 2a00 OK", -1),
                std::make_tuple("HTTP/1.1\r 200 OK", -1)
                ));
}