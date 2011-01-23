#ifndef CONNECTION_IMPL_H_
#define CONNECTION_IMPL_H_

#include "Connection.h"

#include "PlayerId.h"

class AddressedMessage;

class ConnectionImpl : public Connection {
 public:
  ConnectionImpl(const PlayerId& playerId, QTcpSocket* tcpSocket);
  virtual ~ConnectionImpl();

  void connectToHost(const QString& hostName, unsigned int port);
  void disconnectFromHost();
  const PlayerId& getPlayerId() const;

 public slots:
  virtual void handleSendData(const AddressedMessage& message);

 protected slots:
  void readIncommingData();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  PlayerId playerId;
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_IMPL_H_
