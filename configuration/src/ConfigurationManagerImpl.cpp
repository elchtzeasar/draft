#include "ConfigurationManagerImpl.h"

ConfigurationManagerImpl::ConfigurationManagerImpl() : playerName("Unknown player") {}

ConfigurationManagerImpl::~ConfigurationManagerImpl() {
}

const std::string& ConfigurationManagerImpl::getPlayerName() const {
  return playerName;
}

void ConfigurationManagerImpl::setPlayerName(const std::string& playerName) {
  this->playerName = playerName;
}
