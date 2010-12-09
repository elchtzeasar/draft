#include "ConnectionImpl.h"

#include <QTcpSocket>

#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

ConnectionImpl::ConnectionImpl() : tcpSocket(0) {}

void ConnectionImpl::addSocket(QTcpSocket* tcpSocket) {
  this->tcpSocket = tcpSocket;

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readIncommingData()));
  connect(tcpSocket, SIGNAL(connected()), this, SIGNAL(connectedToDraft()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(socketError(QAbstractSocket::SocketError)));
}

void ConnectionImpl::write(QByteArray& block) {
  tcpSocket->write(block);
}

void ConnectionImpl::connectToHost(const QString& hostName, unsigned int port) {
  cout << "Connecting to server at " << hostName.toStdString() << " on port " << port << endl;
  tcpSocket->connectToHost(hostName, port);
}

void ConnectionImpl::disconnectFromHost() {
  tcpSocket->disconnectFromHost();
}

void ConnectionImpl::readIncommingData() {
  char* receivedData;
  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_4_0);
  
  in >> receivedData;
  cout << "Received data: " << receivedData << endl;
}

void ConnectionImpl::socketError(QAbstractSocket::SocketError socketError) {
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
