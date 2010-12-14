#include "StateMachineComponent.h"

#include "AddressedMessage.h"
#include "ClientState.h"
#include "ServerState.h"
#include "State.h"

#include <QSignalTransition>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State(this, static_cast<State*>(0), "ChooseClientOrServer")),
  clientState(new ClientState(this, static_cast<State*>(0), "Client")),
  serverState(new ServerState(this, static_cast<State*>(0), "Server")),
  activeState("Init") {

  connect( this, SIGNAL(dataReceived(const AddressedMessage&)),
	   SLOT(handleDataReceived(const AddressedMessage&)) );

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
void StateMachineComponent::handleDataReceived(const AddressedMessage& message) {
  std::cout << "StateMachineComponent::handleDataReceived("
	    << message << ')' << std::endl;
}

void StateMachineComponent::start() {
  stateMachine->start();
}

StateMachineComponent::~StateMachineComponent() {
  delete clientState;
  delete chooseClientOrServer;
  delete stateMachine;
}
