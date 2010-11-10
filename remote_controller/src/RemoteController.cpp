#include "RemoteController.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

static const unsigned int PORT = 10001;

RemoteController::RemoteController() {}

RemoteController::~RemoteController() {}

void RemoteController::run() {
  while (true) {
    string command;

    cout << '>';
    cin >> command;

    if (command == "host_draft") {
      cout << "Sending host_draft" << endl;
      emit hostDraftSignal(PORT);
      cout << "host_draft sent" << endl;
    } else if (command == "connect_to_draft") {
      cout << "Sending connect_to_draft" << endl;
      emit connectToDraftSignal(PORT);
      cout << "connect_to_draft sent" << endl;
    } else {
      cout << "unknown command: " << command << endl;
    }
  }
}
