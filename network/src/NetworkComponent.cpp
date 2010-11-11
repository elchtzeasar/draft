#include "NetworkComponent.h"

#include "ConnectionListener.h"
#include "Connection.h"

#include <QTcpSocket>

#include <iostream>
#include <cassert>

using std::cout;
using std::cerr;
using std::endl;

NetworkComponent::NetworkComponent() : 
  connection(new Connection),
  connectionListener(new ConnectionListener(*connection)) {}

NetworkComponent::~NetworkComponent() {
  delete connectionListener;
  delete connection;
}

void NetworkComponent::hostDraftSlot(unsigned int port) {
  cout << "NetworkComponent::hostDraft(" << port << ')' << endl;

  connectionListener->listen(port);
}

void NetworkComponent::connectToDraftSlot(unsigned int port) {
  cout << "NetworkComponent::connectToDraft(" << port << ")" << endl;

  connection->addSocket(new QTcpSocket(this));
  connection->connectToHost("localhost", port);
}

