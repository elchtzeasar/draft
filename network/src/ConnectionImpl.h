#ifndef CONNECTION_IMPL_H_
#define CONNECTION_IMPL_H_

#include "Connection.h"

class ConnectionImpl : public Connection {
 public:
  ConnectionImpl();
  virtual ~ConnectionImpl() {}

  void addSocket(QTcpSocket* tcpSocket);
  void write(QByteArray& block);

  void connectToHost(const QString& hostName, unsigned int port);
  void disconnectFromHost();

 protected slots:
  void readIncommingData();
  void connected();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_IMPL_H_
