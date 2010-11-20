#ifndef CONFIGURATION_COMPONENT_FACTORY_H_
#define CONFIGURATION_COMPONENT_FACTORY_H_

class ConfigurationComponent;

class ConfigurationComponentFactory {
 public:
  ConfigurationComponentFactory() {}
  ConfigurationComponent* createComponent();

 private:
  ConfigurationComponentFactory(const ConfigurationComponentFactory&);
  ConfigurationComponentFactory& operator=(ConfigurationComponentFactory&);
};

#endif // CONFIGURATION_COMPONENT_FACTORY_H_
