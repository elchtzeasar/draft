#include "ServerConfiguringState.h"

#include "SendingPlayerIdState.h"
#include "SendingNameState.h"
#include "SavingPlayerNameState.h"

#include <QVariant>

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  sendingPlayerId(new SendingPlayerIdState(component, this)),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  savingPlayerName(new SavingPlayerNameState(component, this)),
  waitingForOtherPlayers(new State(component, this, "WaitingForOtherPlayers")) {

  connect(this, SIGNAL(configurationRequest(quint8)),
	  component, SIGNAL(configurationRequest(quint8)));

  // TODO: Make this dependent on the message type:
  sendingPlayerId->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), receivingClientName);
  // TODO: Make this dependent on the message type:
  receivingClientName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), savingPlayerName);
  // TODO: Make this dependent on the message type:
  savingPlayerName->addTransition(
    component, SIGNAL(dataReceived(const AddressedMessage&)), waitingForOtherPlayers);

  connect(sendingPlayerId, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(savingPlayerName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );

  setInitialState(sendingPlayerId);
}

ServerConfiguringState::~ServerConfiguringState() {
  delete sendingPlayerId;
  delete receivingClientName;
  delete savingPlayerName;
  delete waitingForOtherPlayers;
}

void ServerConfiguringState::sendConfigurationRequest() {
  emit configurationRequest(findProperty("playerId").value<quint8>());
}
