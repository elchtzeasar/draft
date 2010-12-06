#include "StateMachineComponent.h"

#include <QSignalTransition>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State("ChooseClientOrServer")),
  requestingName(new State("RequestingName")),
  activeState("Init") {

  chooseClientOrServer->assignProperty(this, "activeState", "ChooseClientOrServer");
  chooseClientOrServer->addTransition(
    this, SIGNAL(connectToDraft(const QString&, unsigned int)), requestingName);

  requestingName->assignProperty(this, "activeState", "RequestingName");
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
