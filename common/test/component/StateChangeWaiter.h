#ifndef STATE_CHANGE_WAITER_H_
#define STATE_CHANGE_WAITER_H_

#include <QObject>
#include <vector>

class StateChangeWaiter : public QObject {
  Q_OBJECT

 public:
  StateChangeWaiter(const QObject& stateMachineComponent);
  virtual ~StateChangeWaiter();
  bool wait(const QString& stateName);

 private slots:
  void handleStateChanged(const QString& stateName);

 private:
  bool stateEntered(const QString& stateName);

  std::vector<QString> enteredStates;
};

#endif
