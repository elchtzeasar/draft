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

void RemoteController::handleConfigurationResponse(
		const PlayerId&, const QString playerName) {
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
  const unsigned int NR_OF_CHARS(256);
  char cPlayerName[NR_OF_CHARS];
  cin.getline(cPlayerName, NR_OF_CHARS);

  LOG(INFO) << "updatePlayerName: " << cPlayerName;

  QString playerName(cPlayerName + 1); // Skip initial spaces
  emit updatePlayerConfiguration(PlayerId::OWN, playerName);
}

void RemoteController::getPlayerName() {
  LOG(INFO) << "getPlayerName";

  emit configurationRequest(PlayerId::OWN);
}
