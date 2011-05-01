#include "ConnectionImpl.h"

#include "AddressedMessage.h"

#include <QTcpSocket>

#include <glog/logging.h>

ConnectionImpl::ConnectionImpl(QTcpSocket* tcpSocket) :
  tcpSocket(tcpSocket) {

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readIncommingData()));
  connect(tcpSocket, SIGNAL(connected()), this, SIGNAL(connectedToDraft()));
  connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
	  this, SLOT(socketError(QAbstractSocket::SocketError)));
}

ConnectionImpl::~ConnectionImpl() {
  delete tcpSocket;
}

void ConnectionImpl::connectToHost(const QString& hostName, unsigned int port) {
  tcpSocket->connectToHost(hostName, port);
}

void ConnectionImpl::disconnectFromHost() {
  tcpSocket->disconnectFromHost();
}

void ConnectionImpl::sendData(const AddressedMessage& message) const {
  QDataStream out(tcpSocket);
  out.setVersion(QDataStream::Qt_4_0);

  out << message;

  LOG(INFO) << "ConnectionImpl: Message sent: " << message;
}

void ConnectionImpl::readIncommingData() {
  QDataStream in(tcpSocket);
  in.setVersion(QDataStream::Qt_4_0);

  while (!in.atEnd()) {
    AddressedMessage message;
    in >> message;

    LOG(INFO) << "ConnectionImpl: Received message: " << message;

    emit dataReceived(message);
  }
}

void ConnectionImpl::socketError(QAbstractSocket::SocketError socketError) {
  switch (socketError) {
  case QAbstractSocket::RemoteHostClosedError:
    LOG(ERROR) << "The remote host closed";
    break;
  case QAbstractSocket::HostNotFoundError:
    LOG(ERROR) << "The host was not found. Please check the "
	 << "host name and port settings.";
    break;
  case QAbstractSocket::ConnectionRefusedError:
    LOG(ERROR) << "The connection was refused by the peer. "
	 << "Make sure there is a server running, "
	 << "and check that the host name and port "
	 << "settings are correct.";
    break;
  default:
    LOG(ERROR) << "The following error occurred: "
	 << tcpSocket->errorString().toStdString();
  }
}
