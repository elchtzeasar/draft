#include "Connection.h"

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

Connection::Connection() {}

void Connection::addSocket(QTcpSocket* tcpSocket) {
  this->tcpSocket = tcpSocket;

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readIncommingData()));
  connect(tcpSocket, SIGNAL(connected()), this, SLOT(connected()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(socketError(QAbstractSocket::SocketError)));
}

void Connection::write(QByteArray& block) {
  tcpSocket->write(block);
}

void Connection::connectToHost(const char* server, unsigned int port) {
  cout << "Connecting to server at " << server << " on port " << port << endl;
  tcpSocket->connectToHost(server, port);
}

void Connection::disconnectFromHost() {
  tcpSocket->disconnectFromHost();
}

void Connection::readIncommingData() {
  char* receivedData;
  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_4_0);
  
  in >> receivedData;
  cout << "Received data: " << receivedData << endl;
}

void Connection::connected() {
  cout << "Connected to server." << endl;
}

void Connection::socketError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    cerr << "The remote host closed" << endl;
    break;
  case QAbstractSocket::HostNotFoundError:
    cerr << "The host was not found. Please check the "
	 << "host name and port settings.";
    break;
  case QAbstractSocket::ConnectionRefusedError:
    cerr << "The connection was refused by the peer. "
	 << "Make sure the fortune server is running, "
	 << "and check that the host name and port "
	 << "settings are correct.";
    break;
  default:
    cerr << "The following error occurred: "
	 << tcpSocket->errorString().toStdString();
  }
}
