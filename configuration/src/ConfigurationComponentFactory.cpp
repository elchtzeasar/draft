#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationLoaderImpl.h"
#include "PlayerContextImpl.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  PlayerContext* manager = new PlayerContextImpl();
  ConfigurationLoader* loader = new ConfigurationLoaderImpl("configuration.xml", *manager);

  loader->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager, loader);

  return component;
}
