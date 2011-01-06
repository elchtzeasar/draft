#include "ClientStateMachine.h"

#include "ServerConfiguringState.h"

ClientStateMachine::ClientStateMachine(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  configuring(new ServerConfiguringState(component, this, "Configuring")) {

  setInitialState(configuring);
}

ClientStateMachine::~ClientStateMachine() {
  delete configuring;
}
