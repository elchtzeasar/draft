#include "ClientState.h"

#include "ClientConfiguringState.h"

ClientState::ClientState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  configuring(new ClientConfiguringState(component, this, "Configuring")) {

  setInitialState(configuring);
}

ClientState::~ClientState() {
  delete configuring;
}
