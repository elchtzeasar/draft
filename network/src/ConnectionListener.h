#ifndef CONNECTION_LISTENER_H_
#define CONNECTION_LISTENER_H_

#include <QObject>

class Connection;

class ConnectionListener : public QObject {
  Q_OBJECT

 public:
  ~ConnectionListener() {}

  virtual void listen(unsigned int port) = 0;

 signals:
  void clientConnected(quint8 playerId);

 protected slots:
  virtual void acceptConnection() = 0;
};

#endif // CONNECTION_LISTENER_H_
