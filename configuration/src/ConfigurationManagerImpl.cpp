#include "ConfigurationManagerImpl.h"

ConfigurationManagerImpl::~ConfigurationManagerImpl() {}

void ConfigurationManagerImpl::setOwnPlayerId(quint8 playerId) {
}

void ConfigurationManagerImpl::setPlayerContext(quint8 playerId, const std::string& playerName) {
}

const PlayerContext& ConfigurationManagerImpl::getPlayerContext(quint8 playerId) const {
  return *static_cast<PlayerContext*>(NULL);
}
