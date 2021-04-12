#include "gtest.h"
#include "WifiConnectorMock.hpp"
#include "WifiManager.h"

using namespace testing;

namespace WifiManagerTests
{
    TEST(WifiManagerShould, Connect)
    {
        // Arrange
        Network::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Connect(_, _)).Times(Exactly(1));
        Network::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Connect();

        // Assert
    }

    TEST(WifiManagerShould, Disconnect)
    {
        // Arrange
        Network::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Disconnect()).Times(Exactly(1));
        Network::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Disconnect();

        // Assert
    }

    TEST(WifiManagerShould, Reconnect)
    {
        // Arrange
        Network::Wifi::WifiConnectorMock wifiConnectorMock;
        EXPECT_CALL(wifiConnectorMock, Disconnect()).Times(Exactly(1));
        EXPECT_CALL(wifiConnectorMock, Connect(_, _)).Times(Exactly(1));
        Network::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        wifiManager.Reconnect();

        // Assert
    }

    TEST(WifiManagerShould, ReturnTrueIfConnectedToNetwork)
    {
        // Arrange
        Network::Wifi::WifiConnectorMock wifiConnectorMock;
        ON_CALL(wifiConnectorMock, IsConnected()).WillByDefault(Return(true));
        Network::Wifi::WifiManager wifiManager{ wifiConnectorMock, "test", "test" };

        // Act
        auto isConnected = wifiManager.IsConnected();

        // Assert
        EXPECT_TRUE(isConnected);
    }
}
