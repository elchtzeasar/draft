#include "NetworkComponent.h"
#include "NetworkComponentFactoryImpl.h"

#include "SignalWaiter.h"

#include <QSignalSpy>
#include <QTcpSocket>

#include <gtest/gtest.h>

class NetworkComponentTest : public testing::Test {
public:
  NetworkComponentTest() : 
    serverNetworkComponent(serverNetworkComponentFactory.createComponent()),
    clientNetworkComponent(clientNetworkComponentFactory.createComponent()) {}
  ~NetworkComponentTest() {
    delete serverNetworkComponent;
    delete clientNetworkComponent;
  }

protected:
  NetworkComponentFactoryImpl serverNetworkComponentFactory;
  NetworkComponent* serverNetworkComponent;
  NetworkComponentFactoryImpl clientNetworkComponentFactory;
  NetworkComponent* clientNetworkComponent;
};

#include <QTest>

TEST_F(NetworkComponentTest, shouldEmitClientConnectedInServerWhenClientConnects) {
  const unsigned int PORT(12345);
  const QString LOCALHOST("localhost");

  QSignalSpy clientConnectedSpy(serverNetworkComponent, SIGNAL(clientConnected(const PlayerId&)));
  SignalWaiter clientConnectedWaiter(clientConnectedSpy);

  serverNetworkComponent->handleHostDraft(PORT);
  clientNetworkComponent->handleConnectToDraft(LOCALHOST, PORT);

  clientConnectedWaiter.wait();
  ASSERT_EQ(1, clientConnectedSpy.count());
}

TEST_F(NetworkComponentTest, shouldEmitConnectedToDraftInClientWhenConnectedToServer) {
  const unsigned int PORT(12345);
  const QString LOCALHOST("localhost");

  QSignalSpy connectedToServerSpy(clientNetworkComponent, SIGNAL(connectedToDraft()));
  SignalWaiter connectedToServerWaiter(connectedToServerSpy);

  serverNetworkComponent->handleHostDraft(PORT);
  clientNetworkComponent->handleConnectToDraft(LOCALHOST, PORT);

  connectedToServerWaiter.wait();
  ASSERT_EQ(1, connectedToServerSpy.count());
}
