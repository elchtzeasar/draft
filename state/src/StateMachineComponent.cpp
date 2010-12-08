#include "StateMachineComponent.h"

#include "State.h"
#include "ClientState.h"

#include <QSignalTransition>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State(this, static_cast<State*>(0), "ChooseClientOrServer")),
  clientState(new ClientState(this, static_cast<State*>(0), "Client")),
  activeState("Init") {

  chooseClientOrServer->addTransition(
    this, SIGNAL(connectToDraft(const QString&, unsigned int)), clientState);

  stateMachine->addState(chooseClientOrServer);
  stateMachine->addState(clientState);
  stateMachine->setInitialState(chooseClientOrServer);
}

void StateMachineComponent::start() {
  stateMachine->start();
}

StateMachineComponent::~StateMachineComponent() {
  delete clientState;
  delete chooseClientOrServer;
  delete stateMachine;
}
