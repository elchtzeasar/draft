#ifndef CONNECTION_IMPL_H_
#define CONNECTION_IMPL_H_

#include "Connection.h"

class AddressedMessage;

class ConnectionImpl : public Connection {
 public:
  ConnectionImpl(QTcpSocket* tcpSocket);
  virtual ~ConnectionImpl();

  void connectToHost(const QString& hostName, unsigned int port);
  void disconnectFromHost();

 public slots:
  virtual void sendData(const AddressedMessage& message) const;

 protected slots:
  void readIncommingData();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_IMPL_H_
