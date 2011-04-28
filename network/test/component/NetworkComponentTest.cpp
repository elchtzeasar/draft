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

class ComponentWrapper {
public:
    ComponentWrapper(const PlayerId playerId);
    ~ComponentWrapper();

    void host();

    void connectToServerAndWait();

    const PlayerId& getPlayerId() const;
    NetworkComponent& getNetworkComponent();
    QSignalSpy& getClientConnectedSpy();
    const SignalWaiter& getClientConnectedWaiter() const;
    QSignalSpy& getConnectedToServerSpy();
    const SignalWaiter& getConnectedToServerWaiter() const;
    QSignalSpy& getDataReceivedSpy();
    const SignalWaiter& getDataReceivedWaiter() const;
private:
    static const unsigned int PORT;
    static const QString LOCALHOST;

    const PlayerId playerId;
    NetworkComponentFactoryImpl networkComponentFactory;
    NetworkComponent* networkComponent;

    QSignalSpy clientConnectedSpy;
    SignalWaiter clientConnectedWaiter;
    QSignalSpy connectedToServerSpy;
    SignalWaiter connectedToServerWaiter;
    QSignalSpy dataReceivedSpy;
    SignalWaiter dataReceivedWaiter;
};

const unsigned int ComponentWrapper::PORT(12345);
const QString ComponentWrapper::LOCALHOST("localhost");

ComponentWrapper::ComponentWrapper(const PlayerId playerId) :
	        playerId(playerId),
	        networkComponentFactory(),
	        networkComponent(networkComponentFactory.createComponent()),

	        clientConnectedSpy(networkComponent, SIGNAL(clientConnected(const PlayerId&))),
	        clientConnectedWaiter(clientConnectedSpy),
	        connectedToServerSpy(networkComponent, SIGNAL(connectedToDraft())),
	        connectedToServerWaiter(connectedToServerSpy),
	        dataReceivedSpy(networkComponent, SIGNAL(dataReceived(const AddressedMessage&))),
	        dataReceivedWaiter(dataReceivedSpy) {
}

ComponentWrapper::~ComponentWrapper() {
    delete networkComponent;
}

const PlayerId& ComponentWrapper::getPlayerId() const {
    return playerId;
}
NetworkComponent& ComponentWrapper::getNetworkComponent() {
    return *networkComponent;
}
QSignalSpy& ComponentWrapper::getClientConnectedSpy() {
    return clientConnectedSpy;
}
const SignalWaiter& ComponentWrapper::getClientConnectedWaiter() const {
    return clientConnectedWaiter;
}
QSignalSpy& ComponentWrapper::getConnectedToServerSpy() {
    return connectedToServerSpy;
}
const SignalWaiter& ComponentWrapper::getConnectedToServerWaiter() const {
    return connectedToServerWaiter;
}
QSignalSpy& ComponentWrapper::getDataReceivedSpy() {
    return dataReceivedSpy;
}
const SignalWaiter& ComponentWrapper::getDataReceivedWaiter() const {
    return dataReceivedWaiter;
}

void ComponentWrapper::host() {
    networkComponent->handleHostDraft(PORT);
}

void ComponentWrapper::connectToServerAndWait() {
    networkComponent->handleConnectToDraft(LOCALHOST, PORT);

    clientConnectedWaiter.wait();
}


class NetworkComponentTest : public testing::Test {
public:
    NetworkComponentTest() :
        server(PlayerId::SERVER),
        client(0) {}

protected:

    AddressedMessage createAddressedMessage(const PlayerId& senderPlayerId,
                                            const PlayerId& receiverPlayerId) {
        AddressHeader* header(new AddressHeader(senderPlayerId, receiverPlayerId));
        NullMessage* nullMessage(new NullMessage(MessageNumber::NULL_MESSAGE));
        return AddressedMessage(header, nullMessage);
    }

    ComponentWrapper server;
    ComponentWrapper client;
};

TEST_F(NetworkComponentTest, shouldEmitClientConnectedInServerWhenClientConnects) {
    server.host();
    client.connectToServerAndWait();

    server.getClientConnectedWaiter().wait();
    ASSERT_EQ(1, server.getClientConnectedSpy().count());

    QList<QVariant> arguments = server.getClientConnectedSpy().takeFirst();
    const PlayerId& clientAssignedPlayerId(arguments.at(0).value<PlayerId>());
    ASSERT_EQ(client.getPlayerId(), clientAssignedPlayerId);
}

TEST_F(NetworkComponentTest, shouldEmitConnectedToDraftInClientWhenConnectedToServer) {
    server.host();
    client.connectToServerAndWait();

    ASSERT_EQ(1, client.getConnectedToServerSpy().count());
}

TEST_F(NetworkComponentTest, shouldSendDataFromServerToClientCorrectly) {
    const AddressedMessage addressedMessageToSend(
            createAddressedMessage(server.getPlayerId(),
                    client.getPlayerId()));

    server.host();
    client.connectToServerAndWait();

    server.getNetworkComponent().handleSendData(addressedMessageToSend);

    client.getDataReceivedWaiter().wait();
    ASSERT_EQ(1, client.getDataReceivedSpy().count());

    QList<QVariant> arguments = client.getDataReceivedSpy().takeFirst();
    const AddressedMessage& receivedAddressedMessage(arguments.at(0).value<AddressedMessage>());
    ASSERT_EQ(addressedMessageToSend, receivedAddressedMessage);
}

TEST_F(NetworkComponentTest, shouldSendDataFromClientToServerCorrectly) {
    const AddressedMessage addressedMessageToSend(
            createAddressedMessage(client.getPlayerId(),
                    server.getPlayerId()));

    server.host();
    client.connectToServerAndWait();

    client.getNetworkComponent().handleSendData(addressedMessageToSend);

    server.getDataReceivedWaiter().wait();
    ASSERT_EQ(1, server.getDataReceivedSpy().count());

    QList<QVariant> arguments = server.getDataReceivedSpy().takeFirst();
    const AddressedMessage& receivedAddressedMessage(arguments.at(0).value<AddressedMessage>());
    ASSERT_EQ(addressedMessageToSend, receivedAddressedMessage);
}
