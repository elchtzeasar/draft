#include "StateChangeWaiter.h"

#include <QtTest>
#include <algorithm>
#include <glog/logging.h>

using std::find;
using std::vector;

StateChangeWaiter::StateChangeWaiter(const QObject& stateMachineComponent) {
  connect( &stateMachineComponent, SIGNAL(stateChanged(const QString&)),
	   this, SLOT(handleStateChanged(const QString&)) );
}

StateChangeWaiter::~StateChangeWaiter() {}

bool StateChangeWaiter::wait(const QString& stateName) {
  static int const MAX_WAIT = 100;

  for (int waits = 0; waits < MAX_WAIT; ++waits) {
    QTest::qWait(1);
    if (stateEntered(stateName))
        break;
  }

  return stateEntered(stateName);
}

void StateChangeWaiter::handleStateChanged(const QString& stateName) {
  enteredStates.push_back(stateName);
}

bool StateChangeWaiter::stateEntered(const QString& stateName) {
  return find(enteredStates.begin(), enteredStates.end(), stateName) != enteredStates.end();
}
