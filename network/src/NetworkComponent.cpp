#include "NetworkComponent.h"

#include "Connection.h"
#include "ConnectionListener.h"
#include "NetworkComponentFactory.h"
#include <QTcpSocket>

NetworkComponent::NetworkComponent(NetworkComponentFactory& componentFactory,
				   ConnectionListener* connectionListener) 
  : componentFactory(componentFactory),
    connectionListener(connectionListener),
    connection(NULL) {}

NetworkComponent::~NetworkComponent() {
  delete connectionListener;
}

void NetworkComponent::addConnection(const Connection& connection) {
  this->connection = &connection;
}
void NetworkComponent::handleHostDraft(unsigned int port) {
  connectionListener->listen(port);
}

void NetworkComponent::handleConnectToDraft(const QString& hostName, unsigned int port) {
  Connection* connection = componentFactory.createConnection(new QTcpSocket(this));
  connection->connectToHost(hostName, port);
}

void NetworkComponent::handleSendData(const AddressedMessage& message) {
  connection->sendData(message);
}
