#include "ServerState.h"
#include "ClientStateMachine.h"

ServerState::ServerState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  listeningForConnections(new State(component, this, "ListeningForConnections")),
  clientStateMachine(new ClientStateMachine(component, this, "ClientStateMachine")) {

  listeningForConnections->addTransition(component, SIGNAL(clientConnected()), clientStateMachine);

  setInitialState(listeningForConnections);
}

ServerState::~ServerState() {
  delete listeningForConnections;
}
