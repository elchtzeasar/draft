#include "ConnectionListenerImpl.h"

#include "Connection.h"

#include <iostream>

using std::cout;
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

  cout << "Waiting for connections..." << endl;
}

void ConnectionListenerImpl::acceptConnection() {
  connection.addSocket(tcpServer.nextPendingConnection());
  cout << "Received incomming connection from client." << endl;

  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);

  out << "This is server speaking...";

  connection.write(block);
  connection.disconnectFromHost();
}
