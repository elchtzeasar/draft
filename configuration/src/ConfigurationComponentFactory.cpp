#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationLoaderImpl.h"
#include "ConfigurationManagerImpl.h"
#include "PlayerContextImpl.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  ConfigurationManager* manager = new ConfigurationManagerImpl();
  PlayerContext* playerContext = new PlayerContextImpl();
  ConfigurationLoader* loader = new ConfigurationLoaderImpl("configuration.xml", *playerContext);

  loader->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager, loader);

  return component;
}
