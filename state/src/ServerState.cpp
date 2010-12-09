#include "ServerState.h"

ServerState::ServerState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  listeningForConnections(new State(component, this, "ListeningForConnections")) {

  setInitialState(listeningForConnections);
}

ServerState::~ServerState() {
  delete listeningForConnections;
}
