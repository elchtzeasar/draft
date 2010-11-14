#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <QAbstractSocket>
#include <QObject>

class QTcpSocket;
class QString;

class Connection : public QObject {
  Q_OBJECT

 public:
  virtual ~Connection() {}

  virtual void addSocket(QTcpSocket* tcpSocket) = 0;
  virtual void write(QByteArray& block) = 0;

  virtual void connectToHost(const QString& hostName, unsigned int port) = 0;
  virtual void disconnectFromHost() = 0;

 protected slots:
  virtual void readIncommingData() = 0;
  virtual void connected() = 0;
  virtual void socketError(QAbstractSocket::SocketError socketError) = 0;
};

#endif // CONNECTION_H_
