#include "NetworkComponent.h"

#include "Connection.h"
#include "ConnectionListener.h"
#include "NetworkComponentFactory.h"
#include <QTcpSocket>

using std::string;

NetworkComponent::NetworkComponent(NetworkComponentFactory& componentFactory,
				   ConnectionListener* connectionListener) 
  : componentFactory(componentFactory),
    connectionListener(connectionListener) {}

NetworkComponent::~NetworkComponent() {
  delete connectionListener;
}

void NetworkComponent::handleHostDraft(unsigned int port) {
  connectionListener->listen(port);
}

void NetworkComponent::handleConnectToDraft(const QString& hostName, unsigned int port) {
  Connection* connection = componentFactory.createConnection(new QTcpSocket(this));
  connection->connectToHost(hostName, port);
}

