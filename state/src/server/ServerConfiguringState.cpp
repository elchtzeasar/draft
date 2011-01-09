#include "ServerConfiguringState.h"

#include "SendingPlayerIdState.h"
#include "SendingNameState.h"
#include "SavingPlayerNameState.h"

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  sendingPlayerId(new SendingPlayerIdState(component, this)),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  savingPlayerName(new SavingPlayerNameState(component, this)),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingNameState(component, this)) {

  connect(requestingName, SIGNAL(entered()), this, SLOT(sendConfigurationRequest()));
  connect(this, SIGNAL(configurationRequest(quint8)),
	  component, SIGNAL(configurationRequest(quint8)));

  // TODO: Make this dependent on the message type:
  sendingPlayerId->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), receivingClientName);
  // TODO: Make this dependent on the message type:
  receivingClientName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), savingPlayerName);
  savingPlayerName->addTransition(
    savingPlayerName, SIGNAL(entered()), requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(quint8, const QString)), sendingName);

  connect(sendingPlayerId, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );

  setInitialState(sendingPlayerId);
}

ServerConfiguringState::~ServerConfiguringState() {
  delete receivingClientName;
  delete requestingName;
  delete sendingName;
  delete savingPlayerName;
}

void ServerConfiguringState::sendConfigurationRequest() {
  // TODO: Use real playerId here!
  emit configurationRequest(0);
}
