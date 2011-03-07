#include "ConfigurationComponentStub.h"

#include "vlog.h"

#include <sstream>
#include <glog/logging.h>

using std::ostringstream;
using std::string;

ConfigurationComponentStub::ConfigurationComponentStub() : ownPlayerId(PlayerId::NONE) {}

ConfigurationComponentStub::~ConfigurationComponentStub() {}

string ConfigurationComponentStub::getPlayerName(const PlayerId& playerId) const {
  ostringstream s;

  s << "Player #" << playerId;

  return s.str();
}
 
void ConfigurationComponentStub::sendConfigurationResponse(const PlayerId& playerId, const QString playerName) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendConfigurationResponse(playerId=" << playerId
                              << ", playerName=" << playerName.toStdString() << ')';
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

void ConfigurationComponentStub::handleUpdatePlayerConfiguration(const PlayerId& playerId, QString playerName) {
  LOG(WARNING) << "handleUpdatePlayerConfiguration(" << playerId << ", " << playerName.toStdString() << ") called, not doing anything...";
}

void ConfigurationComponentStub::handleSetPlayerName(const PlayerId& playerId, QString playerName) {
  LOG(WARNING) << "handleSetPlayerName(" << playerId << ", " << playerName.toStdString() << ") called, not doing anything...";
}
