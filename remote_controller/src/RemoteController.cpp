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
      exit();
    } else if (command == "set_name") {
      setPlayerName();
    } else if (command == "get_name") {
      getPlayerName();
    } else {
      outputStream << "unknown command: " << command << endl;
    }
  }
}

void RemoteController::configurationResponse(const QString playerName) {
  outputStream << "Player name: " << playerName.toStdString() << endl;
}

void RemoteController::sendHostDraft() {
  outputStream << "Sending host_draft" << endl;
  emit hostDraft(PORT);
  outputStream << "host_draft sent" << endl;
}

void RemoteController::connectToDraft() {
  outputStream << "Sending connect_to_draft" << endl;
  const QString hostName("localhost");
  emit connectToDraft(hostName, PORT);
  outputStream << "connectToDraft sent" << endl;
}

#include <iostream>
void RemoteController::exit() {
  outputStream << "exit!" << endl;
  std::cout << std::flush;
  std::cerr << std::flush;
  ::exit(0);
}

void RemoteController::setPlayerName() {
  string stdPlayerName;
  inputStream >> stdPlayerName;
  QString playerName(stdPlayerName.c_str());
  outputStream << "set_name: " << playerName.toStdString() << endl;
  emit setPlayerName(playerName);
}

void RemoteController::getPlayerName() {
  outputStream << "get_name!" << endl;

  emit configurationRequest();
}
