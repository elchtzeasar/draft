#include "ConfigurationComponent.h"

#include "ConfigurationLoader.h"
#include "PlayerContext.h"

#include <QString>

ConfigurationComponent::ConfigurationComponent(PlayerContext* playerContext, ConfigurationLoader* configurationLoader)
  : playerContext(playerContext), configurationLoader(configurationLoader) {}

ConfigurationComponent::~ConfigurationComponent() {
  delete configurationLoader;
  delete playerContext;
}

void ConfigurationComponent::handleExit(int) {
  configurationLoader->save();
}

void ConfigurationComponent::configurationRequest(quint8 playerId) {
  // TODO: Use the playerId!
  QString playerName = playerContext->getPlayerName().c_str();

  emit configurationResponse(playerId, playerName);
}

#include <iostream>
void ConfigurationComponent::setOwnPlayerId(quint8 playerId) {
  // TODO: Use the playerId to index playerContexts!
  std::cout << "setOwnPlayerId(" << int(playerId) << ')' << std::endl;
}

void ConfigurationComponent::setPlayerName(quint8 playerId, QString playerName) {
  // TODO: Use the playerId!
  playerContext->setPlayerName(playerName.toStdString());
}
