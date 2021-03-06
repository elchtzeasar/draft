#include "StateMachineComponent.h"

#include "AddressedMessage.h"
#include "ClientState.h"
#include "ServerState.h"
#include "State.h"

#include <QSignalTransition>

#include <glog/logging.h>

StateMachineComponent::StateMachineComponent() : 
  stateMachine(new QStateMachine(this)),
  chooseClientOrServer(new State(this, static_cast<State*>(0), "ChooseClientOrServer")),
  clientState(new ClientState(this, static_cast<State*>(0), "Client")),
  serverState(new ServerState(this, static_cast<State*>(0), "Server")),
  activeState("Init") {

  chooseClientOrServer->addTransition(
    this, SIGNAL(connectToDraft(const QString&, unsigned int)), clientState);
  chooseClientOrServer->addTransition(
    this, SIGNAL(hostDraft(unsigned int)), serverState);

  stateMachine->addState(chooseClientOrServer);
  stateMachine->addState(clientState);
  stateMachine->addState(serverState);
  stateMachine->setInitialState(chooseClientOrServer);
}

StateMachineComponent::~StateMachineComponent() {
  delete clientState;
  delete chooseClientOrServer;
  delete stateMachine;
}

void StateMachineComponent::start() {
  stateMachine->start();
}

const QString StateMachineComponent::getActiveState() const {
  return activeState;
}

void StateMachineComponent::setActiveState(QString newState) {
  LOG(INFO) << "StateMachineComponent: STATE CHANGE " << activeState.toStdString().c_str()
	    << " -> " << newState.toStdString().c_str();
  activeState = newState;

  emit stateChanged(activeState);
}
