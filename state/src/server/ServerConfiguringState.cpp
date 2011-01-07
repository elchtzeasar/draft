#include "ServerConfiguringState.h"

#include "SendingNameState.h"
#include "SavingPlayerNameState.h"

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  savingPlayerName(new SavingPlayerNameState(component, this)),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingNameState(component, this)) {

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));

  receivingClientName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), savingPlayerName);
  savingPlayerName->addTransition(
    savingPlayerName, SIGNAL(entered()), requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const QString)), sendingName);

  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );

  setInitialState(receivingClientName);
}

ServerConfiguringState::~ServerConfiguringState() {
  delete receivingClientName;
  delete requestingName;
  delete sendingName;
  delete savingPlayerName;
}
