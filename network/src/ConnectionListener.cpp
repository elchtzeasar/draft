#include "ConnectionListener.h"

#include "Connection.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

ConnectionListener::ConnectionListener(Connection& connection) : connection(connection) {}

ConnectionListener::~ConnectionListener() {
  tcpServer.close();
}

void ConnectionListener::listen(unsigned int port) {
  connect(&tcpServer, SIGNAL(newConnection()), this, SLOT(acceptConnection()));
  if (!tcpServer.listen(QHostAddress::LocalHost, port)) {
    cerr << "Unable to start the server: " << tcpServer.errorString().toStdString() << endl;
    return;
  }

  cout << "Waiting for connections..." << endl;
}

void ConnectionListener::acceptConnection() {
  connection.addSocket(tcpServer.nextPendingConnection());
  cout << "Received incomming connection from client." << endl;

  QByteArray block;
  QDataStream out(&block, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);

  out << "This is server speaking...";

  connection.write(block);
  connection.disconnectFromHost();
}
