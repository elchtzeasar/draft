#include "NetworkComponent.h"
#include "NetworkComponentFactoryImpl.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"
#include "PlayerId.h"

#include "SignalWaiter.h"

#include <QSignalSpy>
#include <QTcpSocket>

#include <gtest/gtest.h>

class NetworkComponentTest : public testing::Test {
public:
  NetworkComponentTest() : 
    serverPlayerId(PlayerId::SERVER),
    serverNetworkComponent(serverNetworkComponentFactory.createComponent()),
    clientConnectedSpy(serverNetworkComponent, SIGNAL(clientConnected(const PlayerId&))),
    clientConnectedWaiter(clientConnectedSpy),

    clientPlayerId(0),
    clientNetworkComponent(clientNetworkComponentFactory.createComponent()),
    connectedToServerSpy(clientNetworkComponent, SIGNAL(connectedToDraft())),
    connectedToServerWaiter(connectedToServerSpy) {}

  ~NetworkComponentTest() {
    delete serverNetworkComponent;
    delete clientNetworkComponent;
  }

protected:

  void hostServer() {
    serverNetworkComponent->handleHostDraft(PORT);
  }

  void connectClientToServerAndWait(NetworkComponent& client) {
    client.handleConnectToDraft(LOCALHOST, PORT);

    clientConnectedWaiter.wait();
  }

  AddressedMessage createAddressedMessage(const PlayerId& senderPlayerId,
				    const PlayerId& receiverPlayerId) {
    AddressHeader* header(new AddressHeader(senderPlayerId, receiverPlayerId));
    NullMessage* nullMessage(new NullMessage(MessageNumber::NULL_MESSAGE));
    return AddressedMessage(header, nullMessage);
  }

  static const unsigned int PORT;
  static const QString LOCALHOST;

  const PlayerId serverPlayerId;
  NetworkComponentFactoryImpl serverNetworkComponentFactory;
  NetworkComponent* serverNetworkComponent;
  QSignalSpy clientConnectedSpy;
  SignalWaiter clientConnectedWaiter;

  const PlayerId clientPlayerId;
  NetworkComponentFactoryImpl clientNetworkComponentFactory;
  NetworkComponent* clientNetworkComponent;
  QSignalSpy connectedToServerSpy;
  SignalWaiter connectedToServerWaiter;
};

const unsigned int NetworkComponentTest::PORT(12345);
const QString NetworkComponentTest::LOCALHOST("localhost");

TEST_F(NetworkComponentTest, shouldEmitClientConnectedInServerWhenClientConnects) {
  hostServer();
  connectClientToServerAndWait(*clientNetworkComponent);

  clientConnectedWaiter.wait();
  ASSERT_EQ(1, clientConnectedSpy.count());

  QList<QVariant> arguments = clientConnectedSpy.takeFirst();
  const PlayerId& clientAssignedPlayerId(arguments.at(0).value<PlayerId>());
  ASSERT_EQ(clientPlayerId, clientAssignedPlayerId);
}

TEST_F(NetworkComponentTest, shouldEmitConnectedToDraftInClientWhenConnectedToServer) {
  hostServer();
  connectClientToServerAndWait(*clientNetworkComponent);

  ASSERT_EQ(1, connectedToServerSpy.count());
}

TEST_F(NetworkComponentTest, shouldSendDataFromServerToClientCorrectly) {
  QSignalSpy dataReceivedInClientSpy(
    clientNetworkComponent, SIGNAL(dataReceived(const AddressedMessage&)));
  SignalWaiter dataReceivedInClientWaiter(dataReceivedInClientSpy);
  const AddressedMessage addressedMessageToSend(
    createAddressedMessage(serverPlayerId, clientPlayerId));

  hostServer();
  connectClientToServerAndWait(*clientNetworkComponent);

  serverNetworkComponent->handleSendData(addressedMessageToSend);

  dataReceivedInClientWaiter.wait();
  ASSERT_EQ(1, dataReceivedInClientSpy.count());

  QList<QVariant> arguments = dataReceivedInClientSpy.takeFirst();
  const AddressedMessage& receivedAddressedMessage(arguments.at(0).value<AddressedMessage>());
  ASSERT_EQ(addressedMessageToSend, receivedAddressedMessage);
}

TEST_F(NetworkComponentTest, shouldSendDataFromClientToServerCorrectly) {
  QSignalSpy dataReceivedInServerSpy(
    serverNetworkComponent, SIGNAL(dataReceived(const AddressedMessage&)));
  SignalWaiter dataReceivedInServerWaiter(dataReceivedInServerSpy);
  const AddressedMessage addressedMessageToSend(
    createAddressedMessage(clientPlayerId, serverPlayerId));

  hostServer();
  connectClientToServerAndWait(*clientNetworkComponent);

  clientNetworkComponent->handleSendData(addressedMessageToSend);

  dataReceivedInServerWaiter.wait();
  ASSERT_EQ(1, dataReceivedInServerSpy.count());

  QList<QVariant> arguments = dataReceivedInServerSpy.takeFirst();
  const AddressedMessage& receivedAddressedMessage(arguments.at(0).value<AddressedMessage>());
  ASSERT_EQ(addressedMessageToSend, receivedAddressedMessage);
}
