#ifndef NETWORK_COMPONENT_FACTORY_H_
#define NETWORK_COMPONENT_FACTORY_H_

class NetworkComponent;

class NetworkComponentFactory {
 public:
  NetworkComponentFactory() {}
  NetworkComponent* createComponent();

 private:
  NetworkComponentFactory(const NetworkComponentFactory&);
  NetworkComponentFactory& operator=(NetworkComponentFactory&);
};

#endif // NETWORK_COMPONENT_FACTORY_H_
