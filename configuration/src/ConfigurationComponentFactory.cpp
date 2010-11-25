#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationManagerImpl.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  ConfigurationManager* manager = new ConfigurationManagerImpl("configuration.xml");
  manager->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager);

  return component;
}
