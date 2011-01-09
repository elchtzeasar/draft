#ifndef CONNECTION_H_
#define CONNECTION_H_

#include <QAbstractSocket>
#include <QObject>

class QTcpSocket;
class QString;
class AddressedMessage;

class Connection : public QObject {
  Q_OBJECT

 public:
  virtual ~Connection() {}

  virtual void connectToHost(const QString& hostName, unsigned int port) = 0;
  virtual void disconnectFromHost() = 0;

 public slots:
  virtual void handleSendData(const AddressedMessage& message) = 0;

 protected slots:
  virtual void readIncommingData() = 0;
  virtual void socketError(QAbstractSocket::SocketError socketError) = 0;

 signals:
  void connectedToDraft();
  void dataReceived(const AddressedMessage& message);
};

#endif // CONNECTION_H_
