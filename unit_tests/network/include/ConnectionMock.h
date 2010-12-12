#ifndef CONNECTION_MOCK_H_
#define CONNECTION_MOCK_H_

#include "Connection.h"

#include <gmock/gmock.h>

class ConnectionMock : public Connection {
 public:
  MOCK_METHOD1(addSocket, void(QTcpSocket* tcpSocket));
  MOCK_METHOD1(write, void(QByteArray& data));

  MOCK_METHOD2(connectToHost, void(const QString& server, unsigned int port));
  MOCK_METHOD0(disconnectFromHost, void());

 public slots:
  MOCK_METHOD1(handleSendData, void(const QByteArray& data));

 protected slots:
  MOCK_METHOD0(readIncommingData, void());
  MOCK_METHOD0(connected, void());
  MOCK_METHOD1(socketError, void(QAbstractSocket::SocketError socketError));
};

#endif // CONNECTION_MOCK_H_
