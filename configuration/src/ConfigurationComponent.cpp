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

void ConfigurationComponent::configurationRequest() {
  QString playerName = configurationManager->getPlayerName().c_str();

  emit configurationResponse(playerName);
}

void ConfigurationComponent::setPlayerName(QString playerName) {
  configurationManager->setPlayerName(playerName.toStdString());
}
