#include "NetworkComponent.h"

#include "ConnectionMock.h"
#include "ConnectionListenerMock.h"
#include "NetworkComponentFactoryMock.h"

#include <QSignalSpy>
#include <QTcpSocket>

#include <gtest/gtest.h>

using testing::_;
using testing::NiceMock;
using testing::Return;
using testing::SaveArg;

class NetworkComponentTest : public testing::Test {
public:
  NetworkComponentTest() : 
    connectionListener(new NiceMock<ConnectionListenerMock>),
    component(networkComponentFactory, connectionListener) {}

protected:
  NiceMock<ConnectionMock> connection;
  NiceMock<ConnectionListenerMock>* connectionListener;
  NiceMock<NetworkComponentFactoryMock> networkComponentFactory;
  NetworkComponent component;
};

static unsigned int PORT(12345);
static const QString HOST("localhost");

TEST_F(NetworkComponentTest, shouldListenWithListenerWhenHostingDraft) {
  EXPECT_CALL(*connectionListener, listen(PORT));

  component.handleHostDraft(PORT);
}

TEST_F(NetworkComponentTest, shouldCreateConnectionWhenConnectingToDraftSlot) {
  EXPECT_CALL(networkComponentFactory, createConnection(_)).WillOnce(Return(&connection));;
  ON_CALL(connection, connectToHost(_, _)).WillByDefault(Return());

  component.handleConnectToDraft(HOST, PORT);
}

TEST_F(NetworkComponentTest, shouldConnectNewConnectionWhenConnectingToDraftSlot) {
  ON_CALL(networkComponentFactory, createConnection(_)).WillByDefault(Return(&connection));;
  EXPECT_CALL(connection, connectToHost(HOST, PORT)).WillOnce(Return());

  component.handleConnectToDraft(HOST, PORT);
}
