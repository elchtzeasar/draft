#include "ConnectionListenerImpl.h"

#include "Connection.h"
#include "NetworkComponentFactory.h"
#include "PlayerId.h"

#include <glog/logging.h>

ConnectionListenerImpl::ConnectionListenerImpl(NetworkComponentFactory& componentFactory) :
  nextPlayerId(0), componentFactory(componentFactory) {
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

  componentFactory.createConnection(tcpServer.nextPendingConnection());

  emit clientConnected(playerId);
}
