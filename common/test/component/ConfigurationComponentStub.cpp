#include "ConfigurationComponentStub.h"

#include <sstream>

using std::ostringstream;

ConfigurationComponentStub::ConfigurationComponentStub() : ownPlayerId(PlayerId::NONE) {}

void ConfigurationComponentStub::handleExit(int) {
}

void ConfigurationComponentStub::handleConfigurationRequest(const PlayerId& playerId) {
  ostringstream s;

  if (playerId == ownPlayerId) {
    s << "Own player";
  } else {
    s << "Player #" << playerId;
  }
  sendConfigurationResponse(playerId, s.str().c_str());
}

void ConfigurationComponentStub::handleSetOwnPlayerId(const PlayerId& playerId) {
  ownPlayerId = playerId;
}

void ConfigurationComponentStub::handleSetPlayerName(const PlayerId& playerId, QString playerName) {
}
 
void ConfigurationComponentStub::sendConfigurationResponse(const PlayerId& playerId, const QString playerName) {
  emit configurationResponse(playerId, playerName);
}
