#ifndef CONNECTION_LISTENER_IMPL_H_
#define CONNECTION_LISTENER_IMPL_H_

#include "ConnectionListener.h"

#include <QTcpServer>

#include <QtGlobal>

class NetworkComponent;
class NetworkComponentFactory;

class ConnectionListenerImpl : public ConnectionListener {
  Q_OBJECT

 public:
  ConnectionListenerImpl(NetworkComponent& networkComponent,
		  NetworkComponentFactory& componentFactory);
  ~ConnectionListenerImpl();

  void listen(unsigned int port);

 protected slots:
  void acceptConnection();

 private:
  ConnectionListenerImpl(const ConnectionListenerImpl&);
  ConnectionListenerImpl& operator=(ConnectionListenerImpl&);

  quint8 nextPlayerId;

  NetworkComponent& networkComponent;
  NetworkComponentFactory& componentFactory;
  QTcpServer tcpServer;
};

#endif // CONNECTION_LISTENER_IMPL_H_
