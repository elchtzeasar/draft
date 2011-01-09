#include "RemoteController.h"

#include <QString>

#include <string>
#include <cstdlib>

using std::endl;
using std::string;

using std::ostream;
using std::istream;

static const unsigned int PORT = 10001;

RemoteController::RemoteController(ostream& outputStream, istream& inputStream )
  : outputStream(outputStream), inputStream(inputStream) {}

RemoteController::~RemoteController() {}

void RemoteController::run() {
  string command;
  while (command != "exit") {
    inputStream >> command;

    if (command == "host_draft") {
      sendHostDraft();
    } else if (command == "connect_to_draft") {
      connectToDraft();
    } else if (command == "exit") {
      exitCommand();
    } else if (command == "set_name") {
      setPlayerName();
    } else if (command == "get_name") {
      getPlayerName();
    } else {
      outputStream << "unknown command: " << command << endl;
    }
  }
}

void RemoteController::configurationResponse(quint8 playerId, const QString playerName) {
  outputStream << "Player name: " << playerName.toStdString() << endl;
}

void RemoteController::sendHostDraft() {
  emit hostDraft(PORT);
}

void RemoteController::connectToDraft() {
  const QString hostName("localhost");
  emit connectToDraft(hostName, PORT);
}

void RemoteController::exitCommand() {
  emit exit(0);
}

void RemoteController::setPlayerName() {
  string stdPlayerName;
  inputStream >> stdPlayerName;
  // TODO (peter): Use real player id:s here!
  QString playerName(stdPlayerName.c_str());
  emit setPlayerName(0, playerName);
}

void RemoteController::getPlayerName() {
  // TODO (peter): Use real player id:s here!
  emit configurationRequest(0);
}
