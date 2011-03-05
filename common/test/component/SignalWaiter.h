#ifndef SIGNAL_WAITER_H_
#define SIGNAL_WAITER_H_

class QSignalSpy;

class SignalWaiter {
public:
  SignalWaiter(QSignalSpy& signalSpy);

  void wait() const;

private:
  QSignalSpy& signalSpy;
};

#endif
