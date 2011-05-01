#include "NetworkComponent.h"

#include "Connection.h"
#include "ConnectionListener.h"
#include "NetworkComponentFactory.h"

#include <QTcpSocket>
#include <cassert>

NetworkComponent::NetworkComponent(NetworkComponentFactory& componentFactory)
  : componentFactory(componentFactory),
    connectionListener(NULL),
    connection(NULL) {}

NetworkComponent::~NetworkComponent() {
  delete connectionListener;
}

void NetworkComponent::addConnection(Connection* connection) {
  this->connection = connection;
}

void NetworkComponent::handleHostDraft(unsigned int port) {
  connectionListener = componentFactory.createConnectionListener();
  connectionListener->listen(port);
}

void NetworkComponent::handleConnectToDraft(const QString& hostName, unsigned int port) {
  connection = componentFactory.createConnection(new QTcpSocket(this));
  connection->connectToHost(hostName, port);
}

void NetworkComponent::handleSendData(const AddressedMessage& message) {
  assert(connection != NULL && "A connection must be added before data can be received!");

  connection->sendData(message);
}
