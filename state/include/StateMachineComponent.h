#ifndef STATE_MACHINE_COMPONENT_H_
#define STATE_MACHINE_COMPONENT_H_

#include <QObject>
#include <QState>
#include <QStateMachine>

#include <iostream>

class State;

class StateMachineComponent : public QObject {
  Q_OBJECT

 public:
  StateMachineComponent();
  virtual ~StateMachineComponent();
  void start();

 signals:
  void connectToDraft(const QString&, unsigned int);
  void configurationRequest();
  void configurationResponse(const QString);

 private:
  Q_PROPERTY(QString activeState READ getActiveState WRITE setActiveState)
  const QString getActiveState() const {
    return activeState;
  }
  void setActiveState(QString newState) {
    std::cout << "StateMachineComponent: STATE CHANGE " << activeState.toStdString().c_str()
	      << " -> " << newState.toStdString().c_str() << std::endl;
    activeState = newState;
  }

  QStateMachine* stateMachine;
  State* chooseClientOrServer;
  State* requestingName;
  QString activeState;
};

#endif // STATE_MACHINE_COMPONENT_H_
