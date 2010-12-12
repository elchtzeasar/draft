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

  virtual void connectToHost(const QString& hostName, unsigned int port) = 0;
  virtual void disconnectFromHost() = 0;

 public slots:
  virtual void handleSendData(const QString& data) = 0;

 protected slots:
  virtual void readIncommingData() = 0;
  virtual void socketError(QAbstractSocket::SocketError socketError) = 0;

 signals:
  void connectedToDraft();
  void dataReceived(const QString& data);
};

#endif // CONNECTION_H_
