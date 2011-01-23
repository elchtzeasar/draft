#include "ConfigurationComponentFactory.h"

#include "ConfigurationComponent.h"
#include "ConfigurationLoaderImpl.h"
#include "ConfigurationManagerImpl.h"
#include "PlayerContextImpl.h"
#include "PlayerContextFactoryImpl.h"

ConfigurationComponent* ConfigurationComponentFactory::createComponent() {
  PlayerContextFactory* playerContextFactory = new PlayerContextFactoryImpl();

  PlayerContext* playerContext = playerContextFactory->createPlayerContext();
  ConfigurationLoader* loader = new ConfigurationLoaderImpl("configuration.xml", *playerContext);

  ConfigurationManager* manager =
    new ConfigurationManagerImpl(playerContext, playerContextFactory);

  loader->load();

  ConfigurationComponent* component = new ConfigurationComponent(manager, loader);

  return component;
}
