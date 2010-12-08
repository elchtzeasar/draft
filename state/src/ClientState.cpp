#include "ClientState.h"

ClientState::ClientState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  requestingName(new State(component, this, "RequestingName")) {  

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));

  setInitialState(requestingName);
}

ClientState::~ClientState() {
  delete requestingName;
}
