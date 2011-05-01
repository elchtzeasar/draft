#include "ConnectionListenerImpl.h"

#include "Connection.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactory.h"
#include "PlayerId.h"

#include <glog/logging.h>

ConnectionListenerImpl::ConnectionListenerImpl(NetworkComponent& networkComponent,
		NetworkComponentFactory& componentFactory) :
  nextPlayerId(0), networkComponent(networkComponent), componentFactory(componentFactory) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
}

ConnectionListenerImpl::~ConnectionListenerImpl() {
  tcpServer.close();
}

void ConnectionListenerImpl::listen(unsigned int port) {
  if (!tcpServer.listen(QHostAddress::Any, port)) {
    LOG(ERROR) << "Unable to start the server: " << tcpServer.errorString().toStdString();
    return;
  }
}

void ConnectionListenerImpl::acceptConnection() {
  PlayerId playerId(nextPlayerId++);

  Connection* connection = componentFactory.createConnection(tcpServer.nextPendingConnection());
  networkComponent.addConnection(connection);

  emit clientConnected(playerId);
}
