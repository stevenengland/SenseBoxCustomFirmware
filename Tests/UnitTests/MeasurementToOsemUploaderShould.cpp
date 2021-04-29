#include <gtest/gtest.h>
#include "MeasurementToOsemUploader.h"
#include "MeasurementConverterMock.hpp"
#include "HttpTerminalMock.hpp"
#include "MeasurementContainerMock.hpp"

using namespace testing;

namespace MeasurementTests
{
    class MeasurementToOsemUploaderShould :public Test {
    protected:
        Network::HttpTerminalMock _httpTerminalMock;
        Measurement::MeasurementContainerMock _containerMock;
        Measurement::MeasurementConverterMock _converterMock;
        Measurement::MeasurementToOsemUploader _uploader
        {
            _httpTerminalMock,
            _converterMock,
            "test.osem.de",
            443,
            "<boxId>",
            "<authToken>"
        };
    };

    TEST_F(MeasurementToOsemUploaderShould, CloseConnection_WhenEndingUpload)
    {
        EXPECT_CALL(_httpTerminalMock, CloseConnection()).Times(1);

        _uploader.EndUpload();
    }

    TEST_F(MeasurementToOsemUploaderShould, ReadResponse)
    {
        EXPECT_CALL(_httpTerminalMock, ReadResponse(_, _, _)).Times(1);

        _uploader.ReadUploadResponse("", 2, 1000);
    }

    TEST_F(MeasurementToOsemUploaderShould, ReturnCompleted_IfSendingDataSucceeds)
    {
        ON_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillByDefault(Return(true));
        ON_CALL(_httpTerminalMock, SendRequestLine(_, _, _)).WillByDefault(Return(1));
        ON_CALL(_httpTerminalMock, SendEmptyLine()).WillByDefault(Return(1));
        ASSERT_EQ(_uploader.TrySendUpload(_containerMock), Completed);
    }

    TEST_F(MeasurementToOsemUploaderShould, ReturnConnectionError_IfSendingDataFails_BecauseConnectionCouldNotBeEstablished)
    {
        EXPECT_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillOnce(Return(false));
        ASSERT_EQ(_uploader.TrySendUpload(_containerMock), ConnectionError);
    }

    TEST_F(MeasurementToOsemUploaderShould, SendAtLeastTwoEmptyLines_WhenSendingData)
    {
        InSequence s;
        ON_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillByDefault(Return(true));
        EXPECT_CALL(_httpTerminalMock, SendRequestLine(_, _, _)).WillOnce(Return(1));
        EXPECT_CALL(_httpTerminalMock, SendHeader(_, _)).Times(AtLeast(1));
        EXPECT_CALL(_httpTerminalMock, SendEmptyLine()).Times(2);

        _uploader.TrySendUpload(_containerMock);
    }

    TEST_F(MeasurementToOsemUploaderShould, CreateCorrectRequestLine_WhenSendingData)
    {
        ON_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillByDefault(Return(true));
        EXPECT_CALL(_httpTerminalMock, SendRequestLine(StrEq("POST"), StrEq("/boxes/<boxId>/data"), StrEq("HTTP/1.1"))).Times(1);

        _uploader.TrySendUpload(_containerMock);
    }

    TEST_F(MeasurementToOsemUploaderShould, ConnectToServer_WhenSendingData)
    {
        EXPECT_CALL(_httpTerminalMock, TryConnect(StrEq("test.osem.de"), 443, true)).Times(1);

        _uploader.TrySendUpload(_containerMock);
    }

    TEST_F(MeasurementToOsemUploaderShould, SendCorrectHeaders_WhenSendingData)
    {
        ON_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillByDefault(Return(true));
        ON_CALL(_httpTerminalMock, SendRequestLine(_, _, _)).WillByDefault(Return(1));
        ON_CALL(_containerMock, Count()).WillByDefault(Return(2));
        EXPECT_CALL(_httpTerminalMock, SendHeader(StrEq("Connection"), StrEq("close"))).Times(1);
        EXPECT_CALL(_httpTerminalMock, SendHeader(StrEq("Authorization"), StrEq("<authToken>"))).Times(1);
        EXPECT_CALL(_httpTerminalMock, SendHeader(StrEq("Host"), StrEq("test.osem.de"))).Times(1);
        EXPECT_CALL(_httpTerminalMock, SendHeader(StrEq("Content-Type"), StrEq("text/csv"))).Times(1);
        EXPECT_CALL(_httpTerminalMock, SendHeader(StrEq("Content-Length"), StrEq("112"))).Times(1);

        _uploader.TrySendUpload(_containerMock);
    }

    TEST_F(MeasurementToOsemUploaderShould, SendCorrectBody_WhenSendingData)
    {
        char* payload = "test";
        ON_CALL(_httpTerminalMock, TryConnect(_, _, _)).WillByDefault(Return(true));
        ON_CALL(_httpTerminalMock, SendRequestLine(_, _, _)).WillByDefault(Return(1));
        ON_CALL(_containerMock, Count()).WillByDefault(Return(2));
        ON_CALL(_containerMock, GetMeasurement(_, _)).WillByDefault(Return(true));
        ON_CALL(_converterMock, Convert(_, _)).WillByDefault(DoAll(SetArrayArgument<1>(payload, payload + strlen(payload) + 1), Return(4)));
        EXPECT_CALL(_httpTerminalMock, SendBody(StrEq("test"))).Times(2);

        _uploader.TrySendUpload(_containerMock);
    }
}