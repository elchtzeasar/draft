#ifndef STATE_MACHINE_COMPONENT_H_
#define STATE_MACHINE_COMPONENT_H_

#include <QObject>
#include <QState>
#include <QStateMachine>

#include <iostream>

class State;
class ClientState;
class ServerState;

class StateMachineComponent : public QObject {
  Q_OBJECT

 public:
  StateMachineComponent();
  virtual ~StateMachineComponent();
  void start();

 signals:
  void hostDraft(unsigned int);
  void clientConnected();

  void connectToDraft(const QString&, unsigned int);
  void connectedToDraft();
  void configurationRequest();
  void configurationResponse(const QString);

  void sendData(const QString&);
  void dataReceived(const QString&);

 public slots:
  void handleDataReceived(const QString& data);

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
  ClientState* clientState;
  ServerState* serverState;
  QString activeState;
};

#endif // STATE_MACHINE_COMPONENT_H_
