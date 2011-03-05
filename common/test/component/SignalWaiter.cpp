#include "SignalWaiter.h"

#include <QSignalSpy>
#include <QTest>

SignalWaiter::SignalWaiter(QSignalSpy& signalSpy) : signalSpy(signalSpy) {
}

void SignalWaiter::wait() const {
  static const int MAX_WAIT = 100;

  for (int waits = 0; waits < MAX_WAIT && signalSpy.count() == 0; ++waits) {
    QTest::qWait(1);
  }
}
