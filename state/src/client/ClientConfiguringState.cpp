#include "ClientConfiguringState.h"

#include "SavingPlayerIdState.h"
#include "SendingNameState.h"

class AddressedMessage;

ClientConfiguringState::ClientConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  receivingPlayerId(new State(component, this, "ReceivingPlayerId")),
  savingPlayerId(new SavingPlayerIdState(component, this)),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingNameState(component, this)),
  receivingPlayerName(new State(component, this, "ReceivingPlayerName")) {

  connect(savingPlayerId, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(savingPlayerId, SIGNAL(setOwnPlayerId(quint8)),
	  component, SIGNAL(setOwnPlayerId(quint8)) );
  connect(requestingName, SIGNAL(entered()), this, SLOT(sendConfigurationRequest()));
  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(this, SIGNAL(configurationRequest(quint8)),
	  component, SIGNAL(configurationRequest(quint8)));

  receivingPlayerId->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), savingPlayerId);
  savingPlayerId->addTransition(requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(quint8, const QString)), sendingName);

  sendingName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), receivingPlayerName);

  setInitialState(receivingPlayerId);
}

ClientConfiguringState::~ClientConfiguringState() {
  delete receivingPlayerId;
  delete savingPlayerId;
  delete requestingName;
  delete sendingName;
  delete receivingPlayerName;
}

void ClientConfiguringState::sendConfigurationRequest() {
  // TODO: Use real playerId here!
  emit configurationRequest(0);
}
