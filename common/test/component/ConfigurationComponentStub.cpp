#include "ConfigurationComponentStub.h"

#include <sstream>
#include <glog/logging.h>

using std::ostringstream;
using std::string;

ConfigurationComponentStub::ConfigurationComponentStub() : ownPlayerId(PlayerId::NONE) {}

ConfigurationComponentStub::~ConfigurationComponentStub() {}

string ConfigurationComponentStub::getPlayerName(const PlayerId& playerId) const {
  ostringstream s;

  if (playerId == ownPlayerId) {
    s << "Own player";
  } else {
    s << "Player #" << playerId;
  }

  return s.str();
}
 
void ConfigurationComponentStub::sendConfigurationResponse(const PlayerId& playerId, const QString playerName) {
  emit configurationResponse(playerId, playerName);
}

void ConfigurationComponentStub::handleExit(int) {
}

void ConfigurationComponentStub::handleConfigurationRequest(const PlayerId& playerId) {
  sendConfigurationResponse(playerId, getPlayerName(playerId).c_str());
}

void ConfigurationComponentStub::handleSetOwnPlayerId(const PlayerId& playerId) {
  ownPlayerId = playerId;
}

void ConfigurationComponentStub::handleSetPlayerName(const PlayerId& playerId, QString playerName) {
  LOG(WARNING) << "handleSetPlayerName(" << playerId << ", " << playerName.toStdString() << ") called, not doing anything...";
}
