#include "StateMachineComponent.h"

#include "State.h"
#include "ClientState.h"
#include "ServerState.h"

#include <QSignalTransition>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State(this, static_cast<State*>(0), "ChooseClientOrServer")),
  clientState(new ClientState(this, static_cast<State*>(0), "Client")),
  serverState(new ServerState(this, static_cast<State*>(0), "Server")),
  activeState("Init") {

  connect( this, SIGNAL(dataReceived(const QString&)),
	   SLOT(handleDataReceived(const QString&)) );

  chooseClientOrServer->addTransition(
    this, SIGNAL(connectToDraft(const QString&, unsigned int)), clientState);
  chooseClientOrServer->addTransition(
    this, SIGNAL(hostDraft(unsigned int)), serverState);

  stateMachine->addState(chooseClientOrServer);
  stateMachine->addState(clientState);
  stateMachine->addState(serverState);
  stateMachine->setInitialState(chooseClientOrServer);
}

// TODO: Remove the following function:
#include <iostream>
void StateMachineComponent::handleDataReceived(const QString& data) {
  std::cout << "StateMachineComponent::handleDataReceived("
	    << data.toStdString().c_str() << ')' << std::endl;
}

void StateMachineComponent::start() {
  stateMachine->start();
}

StateMachineComponent::~StateMachineComponent() {
  delete clientState;
  delete chooseClientOrServer;
  delete stateMachine;
}
