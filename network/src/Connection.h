#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <QTcpSocket>
#include <QObject>

class Connection : public QObject {
  Q_OBJECT

 public:
  Connection();
  virtual ~Connection() {}

  void addSocket(QTcpSocket* tcpSocket);
  void write(QByteArray& block);

  void connectToHost(const char* server, unsigned int port);
  void disconnectFromHost();

 private slots:
  void readIncommingData();
  void socketError(QAbstractSocket::SocketError socketError);

 private:
  QTcpSocket* tcpSocket;
};

#endif // CONNECTION_H_
