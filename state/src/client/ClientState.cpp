#include "ClientState.h"

#include "AddressHeader.h"
#include "ClientConfiguringState.h"

ClientState::ClientState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  playerId(AddressHeader::NO_PLAYER_ID),
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
