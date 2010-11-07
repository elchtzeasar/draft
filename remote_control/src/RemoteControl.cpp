#include "RemoteControl.h"

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

RemoteControl::RemoteControl() {}

RemoteControl::~RemoteControl() {}

void RemoteControl::run() {
  while (true) {
    string command;
    cin >> command;
    cout << "C++: " << command << endl;
  }
}
