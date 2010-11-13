#include "NetworkComponent.h"

#include "Connection.h"
#include "ConnectionListener.h"

#include <QTcpSocket>

#include <iostream>
#include <cassert>

using std::cout;
using std::cerr;
using std::endl;

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

void NetworkComponent::connectToDraftSlot(unsigned int port) {
  connection->addSocket(new QTcpSocket(this));
  connection->connectToHost("localhost", port);
}

