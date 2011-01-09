#ifndef CONNECTION_LISTENER_IMPL_H_
#define CONNECTION_LISTENER_IMPL_H_

#include "ConnectionListener.h"

#include <QTcpServer>

class NetworkComponentFactory;

class ConnectionListenerImpl : public ConnectionListener {
  Q_OBJECT

 public:
  ConnectionListenerImpl(NetworkComponentFactory& componentFactory);
  ~ConnectionListenerImpl();

  void listen(unsigned int port);

 protected slots:
  void acceptConnection();

 private:
  ConnectionListenerImpl(const ConnectionListenerImpl&);
  ConnectionListenerImpl& operator=(ConnectionListenerImpl&);

  NetworkComponentFactory& componentFactory;
  QTcpServer tcpServer;
};

#endif // CONNECTION_LISTENER_IMPL_H_
