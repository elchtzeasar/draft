#ifndef CONNECTION_IMPL_H_
#define CONNECTION_IMPL_H_

#include "Connection.h"

class AddressedMessage;

class ConnectionImpl : public Connection {
 public:
  ConnectionImpl(quint8 playerId, QTcpSocket* tcpSocket);
  virtual ~ConnectionImpl();

  void connectToHost(const QString& hostName, unsigned int port);
  void disconnectFromHost();
  quint8 getPlayerId() const;

 public slots:
  virtual void handleSendData(const AddressedMessage& message);

 protected slots:
  void readIncommingData();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  quint8 playerId;
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_IMPL_H_
