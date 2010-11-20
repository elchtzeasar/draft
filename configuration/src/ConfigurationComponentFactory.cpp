#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationManager.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  ConfigurationManager* manager = new ConfigurationManager("configuration.xml");
  manager->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager);

  return component;
}
