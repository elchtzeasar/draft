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
    cout << "C++: " << command << endl;
  }
}
