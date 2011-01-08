#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationLoaderImpl.h"
#include "ConfigurationManagerImpl.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  ConfigurationManager* manager = new ConfigurationManagerImpl();
  ConfigurationLoader* loader = new ConfigurationLoaderImpl("configuration.xml", *manager);

  loader->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager, loader);

  return component;
}
