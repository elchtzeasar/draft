#include "NetworkComponent.h"

#include "ConnectionMock.h"
#include "ConnectionListenerMock.h"

#include <QTcpSocket>

#include <gtest/gtest.h>

using testing::_;
using testing::SaveArg;

class NetworkComponentTest : public testing::Test {
public:
  NetworkComponentTest() : 
    connection(new ConnectionMock),
    connectionListener(new ConnectionListenerMock),
    component(connection, connectionListener) {}

protected:
  ConnectionMock* connection;
  ConnectionListenerMock* connectionListener;
  NetworkComponent component;
};

static unsigned int PORT = 12345;

TEST_F(NetworkComponentTest, shouldListenWithListenerWhenHostingDraft) {
  EXPECT_CALL(*connectionListener, listen(PORT));

  component.hostDraftSlot(PORT);
}

TEST_F(NetworkComponentTest, shouldCreateSocketAndConnectToHostWhenConnectingToDraftSlot) {
  QTcpSocket* socket = 0;

  EXPECT_CALL(*connection, addSocket(_)).WillOnce(SaveArg<0>(&socket));
  EXPECT_CALL(*connection, connectToHost("localhost", PORT));

  component.connectToDraftSlot(PORT);

  ASSERT_NE(static_cast<QTcpSocket*>(0), socket);
}
