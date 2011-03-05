#include "ConfigurationComponent.h"

#include "ConfigurationManager.h"
#include "ConfigurationLoader.h"
#include "PlayerContext.h"

#include <QString>

ConfigurationComponent::ConfigurationComponent(ConfigurationManager* configurationManager,
					       ConfigurationLoader* configurationLoader)
  : configurationManager(configurationManager), configurationLoader(configurationLoader) {}

ConfigurationComponent::~ConfigurationComponent() {
  delete configurationLoader;
  delete configurationManager;
}

void ConfigurationComponent::handleExit(int) {
  configurationLoader->save();
}

void ConfigurationComponent::handleConfigurationRequest(const PlayerId& playerId) {
  const PlayerContext& playerContext = configurationManager->getPlayerContext(playerId);

  emit configurationResponse(playerId, playerContext.getPlayerName());
}

void ConfigurationComponent::handleSetOwnPlayerId(const PlayerId& playerId) {
  configurationManager->setOwnPlayerId(playerId);
}

void ConfigurationComponent::handleSetPlayerName(const PlayerId& playerId, const QString& playerName) {
  configurationManager->setPlayerContext(playerId, playerName);
}
