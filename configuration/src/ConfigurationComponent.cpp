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
  const QString playerName(playerContext.getPlayerName().c_str());

  emit configurationResponse(playerId, playerName);
}

void ConfigurationComponent::handleSetOwnPlayerId(const PlayerId& playerId) {
  configurationManager->setOwnPlayerId(playerId);
}

void ConfigurationComponent::handleSetPlayerName(const PlayerId& playerId, QString playerName) {
  configurationManager->setPlayerContext(playerId, playerName.toStdString());
}
