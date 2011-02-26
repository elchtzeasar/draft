#include "StateChangeWaiter.h"

#include <QtTest>
#include <glog/logging.h>

StateChangeWaiter::StateChangeWaiter(const QObject& stateMachineComponent) {
  connect( &stateMachineComponent, SIGNAL(stateChanged()),
	   this, SLOT(handleStateChanged()) );
}

StateChangeWaiter::~StateChangeWaiter() {}

bool StateChangeWaiter::wait() {
  static int const MAX_WAIT = 100;

  for (int waits = 0; waits < MAX_WAIT && !stateChanged; ++waits)
    QTest::qWait(1);

  const bool returnValue(stateChanged);
  stateChanged = false;

  return returnValue;
}

void StateChangeWaiter::handleStateChanged() {
  stateChanged = true;
}
