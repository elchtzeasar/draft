#include "ConfigurationComponent.h"

#include "ConfigurationManager.h"

#include <QString>

ConfigurationComponent::ConfigurationComponent(ConfigurationManager* configurationManager)
  : configurationManager(configurationManager) {}

ConfigurationComponent::~ConfigurationComponent() {
  //configurationManager->save();
  delete configurationManager;
}

void ConfigurationComponent::configurationRequest() {
  QString playerName = configurationManager->getPlayerName().c_str();

  emit configurationResponse(playerName);
}

void ConfigurationComponent::setPlayerName(QString playerName) {
  configurationManager->setPlayerName(playerName.toStdString());
}
