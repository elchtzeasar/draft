#ifndef NETWORK_COMPONENT_FACTORY_IMPL_H_
#define NETWORK_COMPONENT_FACTORY_IMPL_H_

#include "NetworkComponentFactory.h"

#include <QtGlobal>

class QTcpSocket;

class NetworkComponentFactoryImpl : public NetworkComponentFactory {
 public:
  NetworkComponentFactoryImpl();
  virtual ~NetworkComponentFactoryImpl() {}

  NetworkComponent* createComponent();
  Connection* createConnection(QTcpSocket* tcpSocket);

 private:
  NetworkComponentFactoryImpl(const NetworkComponentFactoryImpl&);
  NetworkComponentFactoryImpl& operator=(NetworkComponentFactoryImpl&);

  quint8 nextPlayerId;
  NetworkComponent* networkComponent;
};

#endif // NETWORK_COMPONENT_FACTORY_IMPL_H_
