#include "RemoteControllerStub.h"

void RemoteControllerStub::run() {
}
  
void RemoteControllerStub::sendExit(int status) {
  emit exit(status);
}

void RemoteControllerStub::sendHostDraft(unsigned int port) {
  emit hostDraft(port);
}

void RemoteControllerStub::sendConnectToDraft(const QString& hostName, unsigned int port) {
  emit connectToDraft(hostName, port);
}

void RemoteControllerStub::sendSetPlayerName(const PlayerId& playerId, QString playerName) {
  emit setPlayerName(playerId, playerName);
}

void RemoteControllerStub::sendConfigurationRequest(const PlayerId& playerId) {
  emit configurationRequest(playerId);
}


void RemoteControllerStub::handleConfigurationResponse(const PlayerId& playerId, const QString playerName) {
}
