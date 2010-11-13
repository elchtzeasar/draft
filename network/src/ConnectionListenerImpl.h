#ifndef CONNECTION_LISTENER_IMPL_H_
#define CONNECTION_LISTENER_IMPL_H_

#include "ConnectionListener.h"

#include <QTcpServer>

class ConnectionListenerImpl : public ConnectionListener {
  Q_OBJECT

 public:
  ConnectionListenerImpl(Connection& connection);
  ~ConnectionListenerImpl();

  void listen(unsigned int port);

 protected slots:
  void acceptConnection();

 private:
  Connection& connection;
  QTcpServer tcpServer;
};

#endif // CONNECTION_LISTENER_IMPL_H_
