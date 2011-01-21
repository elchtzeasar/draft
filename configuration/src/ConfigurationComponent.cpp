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

void ConfigurationComponent::configurationRequest(quint8 playerId) {
  const PlayerContext& playerContext = configurationManager->getPlayerContext(playerId);
  const QString playerName(playerContext.getPlayerName().c_str());

  emit configurationResponse(playerId, playerName);
}

void ConfigurationComponent::setOwnPlayerId(quint8 playerId) {
  configurationManager->setOwnPlayerId(playerId);
}

void ConfigurationComponent::setPlayerName(quint8 playerId, QString playerName) {
  configurationManager->setPlayerContext(playerId, playerName.toStdString());
}
