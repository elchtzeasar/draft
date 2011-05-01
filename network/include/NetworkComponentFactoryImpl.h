#ifndef NETWORK_COMPONENT_FACTORY_IMPL_H_
#define NETWORK_COMPONENT_FACTORY_IMPL_H_

#include "NetworkComponentFactory.h"

class QTcpSocket;

class NetworkComponentFactoryImpl : public NetworkComponentFactory {
 public:
  NetworkComponentFactoryImpl();
  virtual ~NetworkComponentFactoryImpl() {}

  NetworkComponent* createComponent();
  Connection* createConnection(QTcpSocket* tcpSocket);
  ConnectionListener* createConnectionListener();

 private:
  NetworkComponentFactoryImpl(const NetworkComponentFactoryImpl&);
  NetworkComponentFactoryImpl& operator=(NetworkComponentFactoryImpl&);

  NetworkComponent* networkComponent;
};

#endif // NETWORK_COMPONENT_FACTORY_IMPL_H_
