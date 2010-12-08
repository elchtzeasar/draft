#include "StateMachineComponent.h"

#include "State.h"

#include <QSignalTransition>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State(this, 0, "ChooseClientOrServer")),
  requestingName(new State(this, 0, "RequestingName")),
  activeState("Init") {

  chooseClientOrServer->addTransition(
    this, SIGNAL(connectToDraft(const QString&, unsigned int)), requestingName);

  connect(requestingName, SIGNAL(entered()), this, SIGNAL(configurationRequest()));

  stateMachine->addState(chooseClientOrServer);
  stateMachine->addState(requestingName);
  stateMachine->setInitialState(chooseClientOrServer);
}

void StateMachineComponent::start() {
  stateMachine->start();
}

StateMachineComponent::~StateMachineComponent() {
  delete requestingName;
  delete stateMachine;
}
