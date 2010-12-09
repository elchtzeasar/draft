#include "ClientConfiguringState.h"

ClientConfiguringState::ClientConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new State(component, this, "SendingName")) {

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));

  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const QString)), sendingName);

  setInitialState(requestingName);
}

ClientConfiguringState::~ClientConfiguringState() {
  delete sendingName;
  delete requestingName;
}
