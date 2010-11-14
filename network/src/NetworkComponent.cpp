#include "NetworkComponent.h"

#include "Connection.h"
#include "ConnectionListener.h"

#include <QTcpSocket>

using std::string;

NetworkComponent::NetworkComponent(
  Connection* connection, ConnectionListener* connectionListener) 
  : connection(connection),
    connectionListener(connectionListener) {}

NetworkComponent::~NetworkComponent() {
  delete connection;
  delete connectionListener;
}

void NetworkComponent::hostDraftSlot(unsigned int port) {
  connectionListener->listen(port);
}

void NetworkComponent::connectToDraftSlot(const QString& hostName, unsigned int port) {
  connection->addSocket(new QTcpSocket(this));
  connection->connectToHost(hostName, port);
}

