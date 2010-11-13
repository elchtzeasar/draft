#include "RemoteController.h"

#include <string>

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
      outputStream << "Sending host_draft" << endl;
      emit hostDraftSignal(PORT);
      outputStream << "host_draft sent" << endl;
    } else if (command == "connect_to_draft") {
      outputStream << "Sending connect_to_draft" << endl;
      emit connectToDraftSignal(PORT);
      outputStream << "connect_to_draft sent" << endl;
    } else if (command == "exit") {
      outputStream << "exit!" << endl;
    } else {
      outputStream << "unknown command: " << command << endl;
    }
  }
}
