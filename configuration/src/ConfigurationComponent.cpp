#include "ConfigurationComponent.h"

#include "ConfigurationManager.h"

#include <QString>

ConfigurationComponent::ConfigurationComponent(const ConfigurationManager* configurationManager)
  : configurationManager(configurationManager) {}

ConfigurationComponent::~ConfigurationComponent() {
  //configurationManager->save();
  delete configurationManager;
}

#include <iostream>
void ConfigurationComponent::configurationRequest() {
  QString playerName = configurationManager->getPlayerName().c_str();

  emit configurationResponse(playerName);
}
