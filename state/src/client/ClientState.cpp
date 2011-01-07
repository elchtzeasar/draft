#include "ClientState.h"

#include "ClientConfiguringState.h"

ClientState::ClientState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  waitingForConnection(new State(component, this, "WaitingForConnection")),
  configuring(new ClientConfiguringState(component, this, "Configuring")) {

  waitingForConnection->addTransition(component, SIGNAL(connectedToDraft()), configuring);

  setInitialState(waitingForConnection);
}

ClientState::~ClientState() {
  delete waitingForConnection;
  delete configuring;
}
