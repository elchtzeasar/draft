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
  receivingPlayerList(new State(receivingPlayerList, this, "ReceivingPlayerList")) {

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));
  connect(savingPlayerId, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );

  receivingPlayerId->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), savingPlayerId);
  savingPlayerId->addTransition(requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const QString)), sendingName);
  sendingName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), receivingPlayerList);

  setInitialState(receivingPlayerId);
}

ClientConfiguringState::~ClientConfiguringState() {
  delete sendingName;
  delete requestingName;
}
