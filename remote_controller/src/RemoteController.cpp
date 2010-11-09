#include "RemoteController.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

RemoteController::RemoteController() {}

RemoteController::~RemoteController() {}

void RemoteController::run() {
  while (true) {
    string command;
    cin >> command;

    if (command == "host_draft") {
      cout << "Sending host_draft" << endl;
      emit hostDraftSignal(100);
      cout << "host_draft sent" << endl;
    } else if (command == "connect_to_draft") {
      cout << "Sending connect_to_draft" << endl;
      emit connectToDraftSignal();
      cout << "connect_to_draft sent" << endl;
    } else {
      cout << "unknown command: " << command << endl;
    }
  }
}
