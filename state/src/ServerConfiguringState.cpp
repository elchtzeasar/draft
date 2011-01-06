#include "ServerConfiguringState.h"

#include "WaitingForAllPlayersToConnectState.h"

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  waitingForAllPlayersToConnect(new WaitingForAllPlayersToConnectState(component, this)) {

  receivingClientName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), waitingForAllPlayersToConnect);

  setInitialState(receivingClientName);
}

ServerConfiguringState::~ServerConfiguringState() {
  delete receivingClientName;
  delete waitingForAllPlayersToConnect;
}
