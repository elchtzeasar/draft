#include "ConnectionListenerImpl.h"

#include "Connection.h"

#include <iostream>

using std::cerr;
using std::endl;

ConnectionListenerImpl::ConnectionListenerImpl(Connection& connection) : connection(connection) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  connect(&tcpServer, SIGNAL(newConnection()), this, SIGNAL(clientConnected()));
}

ConnectionListenerImpl::~ConnectionListenerImpl() {
  tcpServer.close();
}

void ConnectionListenerImpl::listen(unsigned int port) {
  if (!tcpServer.listen(QHostAddress::Any, port)) {
    cerr << "Unable to start the server: " << tcpServer.errorString().toStdString() << endl;
    return;
  }
}

void ConnectionListenerImpl::acceptConnection() {
  connection.addSocket(tcpServer.nextPendingConnection());

  //connection.handleSendData(QString("This is server speaking..."));
}
