#include "gtest.h"
#include "WifiConnectorMock.hpp"
#include "WifiManager.h"

using namespace testing;

namespace WifiManagerTests
{
    TEST(WifiManagerShould, Connect)
    {
        // Arrange
        Connectivity::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Connect(_, _)).Times(Exactly(1));
        const Connectivity::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Connect();

        // Assert
    }

    TEST(WifiManagerShould, Disconnect)
    {
        // Arrange
        Connectivity::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Disconnect()).Times(Exactly(1));
        const Connectivity::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Disconnect();

        // Assert
    }

    TEST(WifiManagerShould, Reconnect)
    {
        // Arrange
        Connectivity::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Disconnect()).Times(Exactly(1));
        EXPECT_CALL(wifiConnectorMock, Connect(_, _)).Times(Exactly(1));
        const Connectivity::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Reconnect();

        // Assert
    }

    TEST(WifiManagerShould, ReturnTrueIfConnectedToNetwork)
    {
        // Arrange
        Connectivity::Wifi::WifiConnectorMock wifiConnectorMock;
        ON_CALL(wifiConnectorMock, IsConnected()).WillByDefault(Return(true));
        const Connectivity::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        const auto isConnected = wifiManager.IsConnected();

        // Assert
        EXPECT_TRUE(isConnected);
    }
}
