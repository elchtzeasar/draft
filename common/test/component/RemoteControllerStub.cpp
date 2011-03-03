#include "RemoteControllerStub.h"

#include "PlayerId.h"
#include "vlog.h"

#include <QString>
#include <glog/logging.h>

RemoteControllerStub::~RemoteControllerStub() {}

void RemoteControllerStub::run() {
}
  
void RemoteControllerStub::sendExit(int status) {
  emit exit(status);
}

void RemoteControllerStub::sendHostDraft(unsigned int port) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendHostDraft(port=" << port << ')';
  emit hostDraft(port);
}

void RemoteControllerStub::sendConnectToDraft(const QString& hostName, unsigned int port) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendHostDraft(hostName=" << hostName.toStdString() << ", "
                              << "port=" << port << ')';
  emit connectToDraft(hostName, port);
}

void RemoteControllerStub::sendSetPlayerName(const PlayerId& playerId, QString playerName) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendHostDraft(playerId=" << playerId << ", "
                              << "playerName=" << playerName.toStdString() << ')';
  emit setPlayerName(playerId, playerName);
}

void RemoteControllerStub::sendConfigurationRequest(const PlayerId& playerId) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendHostDraft(playerId=" << playerId << ')';
  emit configurationRequest(playerId);
}


void RemoteControllerStub::handleConfigurationResponse(const PlayerId& playerId, const QString playerName) {
  LOG(WARNING) << "handleConfigurationResponse(playerId=" << playerId
               << ", playerName=" << playerName.toStdString() 
	       << ") called, not doing anything...";
}

void RemoteControllerStub::handleConnectedToServer() {
  LOG(WARNING) << "handleConnectedToServer() called, not doing anything...";
}

void RemoteControllerStub::handlePlayerConnected(const PlayerId& playerId, const QString& playerName) {
  LOG(WARNING) << "handlePlayerConnected(playerId=" << playerId
               << ", playerName=" << playerName.toStdString() 
	       << ") called, not doing anything...";
}
