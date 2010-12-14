#ifndef CONNECTION_IMPL_H_
#define CONNECTION_IMPL_H_

#include "Connection.h"

class AddressedMessage;

class ConnectionImpl : public Connection {
 public:
  ConnectionImpl();
  virtual ~ConnectionImpl() {}

  void addSocket(QTcpSocket* tcpSocket);

  void connectToHost(const QString& hostName, unsigned int port);
  void disconnectFromHost();

 public slots:
  virtual void handleSendData(const AddressedMessage& message);

 protected slots:
  void readIncommingData();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_IMPL_H_
