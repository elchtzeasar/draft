#include "ClientState.h"

#include "ClientConfiguringState.h"
#include "PlayerId.h"

ClientState::ClientState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  playerId(qVariantFromValue(PlayerId::NONE)),
  waitingForConnection(new State(component, this, "WaitingForConnection")),
  configuring(new ClientConfiguringState(component, this, "Configuring")) {

  setProperty("playerId", playerId);

  waitingForConnection->addTransition(component, SIGNAL(connectedToDraft()), configuring);

  setInitialState(waitingForConnection);
}

ClientState::~ClientState() {
  delete waitingForConnection;
  delete configuring;
}
