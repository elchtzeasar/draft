#include "RemoteController.h"

#include "PlayerId.h"

#include <glog/logging.h>
#include <QString>

#include <string>
#include <cstdlib>

using std::cin;
using std::endl;
using std::string;

using std::istream;
using std::ostream;

static const unsigned int PORT = 10001;

RemoteController::RemoteController() {}

RemoteController::~RemoteController() {}

void RemoteController::run() {
  string command;
  while (command != "exit") {
    cin >> command;

    if (command == "host_draft") {
      sendHostDraft();
    } else if (command == "connect_to_draft") {
      connectToDraft();
    } else if (command == "exit") {
      exitCommand();
    } else if (command == "set_name") {
      updatePlayerName();
    } else if (command == "get_name") {
      getPlayerName();
    } else {
      LOG(ERROR) << "unknown command: " << command << endl;
    }
  }
}

void RemoteController::handleConfigurationResponse(const PlayerId& playerId,
						   const QString playerName) {
  LOG(INFO) << "Player name: " << playerName.toStdString() << endl;
}

void RemoteController::handleConnectedToServer() {
  LOG(INFO) << "Connected to server" << endl;
}

void RemoteController::handlePlayerConnected(const PlayerId&, const QString& playerName) {
  LOG(INFO) << playerName.toStdString() << " connected" << endl;
}

void RemoteController::sendHostDraft() {
  LOG(INFO) << "sendHostDraft";

  emit hostDraft(PORT);
}

void RemoteController::connectToDraft() {
  LOG(INFO) << "connectToDraft";

  const QString hostName("localhost");
  emit connectToDraft(hostName, PORT);
}

void RemoteController::exitCommand() {
  LOG(INFO) << "exitCommand";

  emit exit(0);
}

void RemoteController::updatePlayerName() {
  string stdPlayerName;
  cin >> stdPlayerName;

  LOG(INFO) << "updatePlayerName: " << stdPlayerName;

  QString playerName(stdPlayerName.c_str());
  emit updatePlayerConfiguration(PlayerId::OWN, playerName);
}

void RemoteController::getPlayerName() {
  LOG(INFO) << "getPlayerName";

  emit configurationRequest(PlayerId::OWN);
}
