#include "ServerConfiguringState.h"

#include "SendingNameState.h"
#include "WaitingForAllPlayersToConnectState.h"

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingNameState(component, this)),
  waitingForAllPlayersToConnect(new WaitingForAllPlayersToConnectState(component, this)) {

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));

  receivingClientName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const QString)), sendingName);
  sendingName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), waitingForAllPlayersToConnect);

  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );

  setInitialState(receivingClientName);
}

ServerConfiguringState::~ServerConfiguringState() {
  delete receivingClientName;
  delete waitingForAllPlayersToConnect;
}
