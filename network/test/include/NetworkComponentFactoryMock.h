#ifndef NETWORK_COMPONENT_FACTORY_MOCK_H_
#define NETWORK_COMPONENT_FACTORY_MOCK_H_

#include "NetworkComponentFactory.h"

class NetworkComponentFactoryMock : public NetworkComponentFactory {
 public:
  virtual ~NetworkComponentFactoryMock() {}

  MOCK_METHOD0(createComponent, NetworkComponent*());
  MOCK_METHOD1(createConnection, Connection*(QTcpSocket* tcpSocket));
  MOCK_METHOD0(createConnectionListener, ConnectionListener*());
};

#endif // NETWORK_COMPONENT_FACTORY_MOCK_H_
