#include "ConfigurationComponent.h"

#include "ConfigurationLoader.h"
#include "ConfigurationManager.h"

#include <QString>

ConfigurationComponent::ConfigurationComponent(ConfigurationManager* configurationManager, ConfigurationLoader* configurationLoader)
  : configurationManager(configurationManager), configurationLoader(configurationLoader) {}

ConfigurationComponent::~ConfigurationComponent() {
  delete configurationLoader;
  delete configurationManager;
}

void ConfigurationComponent::handleExit(int) {
  configurationLoader->save();
}

void ConfigurationComponent::configurationRequest(quint8 playerId) {
  // TODO: Use the playerId!
  QString playerName = configurationManager->getPlayerName().c_str();

  emit configurationResponse(playerId, playerName);
}

void ConfigurationComponent::setPlayerName(quint8 playerId, QString playerName) {
  // TODO: Use the playerId!
  configurationManager->setPlayerName(playerName.toStdString());
}
