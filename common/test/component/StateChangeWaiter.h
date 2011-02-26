#ifndef STATE_CHANGE_WAITER_H_
#define STATE_CHANGE_WAITER_H_

#include <QObject>

class StateChangeWaiter : public QObject {
  Q_OBJECT

 public:
  StateChangeWaiter(const QObject& stateMachineComponent);
  virtual ~StateChangeWaiter();
  bool wait();

 private slots:
  void handleStateChanged();

 private:
  bool stateChanged;
};

#endif
