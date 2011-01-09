#ifndef NETWORK_COMPONENT_FACTORY_H_
#define NETWORK_COMPONENT_FACTORY_H_

class Connection;
class NetworkComponent;

class QTcpSocket;

class NetworkComponentFactory {
 public:
  virtual ~NetworkComponentFactory() {}

  virtual NetworkComponent* createComponent() = 0;
  virtual Connection* createConnection(QTcpSocket* tcpSocket) = 0;
};

#endif // NETWORK_COMPONENT_FACTORY_H_
