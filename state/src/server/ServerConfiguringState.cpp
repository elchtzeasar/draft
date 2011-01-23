#include "ServerConfiguringState.h"

#include "Message.h"
#include "PlayerId.h"
#include "ReceivedMessageTransition.h"
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

  connect(this, SIGNAL(configurationRequest(const PlayerId&)),
	  component, SIGNAL(configurationRequest(const PlayerId&)));

  new ReceivedMessageTransition(
    component, sendingPlayerId, receivingClientName, PLAYER_ID_CNF);
  new ReceivedMessageTransition(
    component, receivingClientName, savingPlayerName, PLAYER_NAME_CFG);
  savingPlayerName->addTransition(waitingForOtherPlayers);

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
  emit configurationRequest(findProperty("playerId").value<PlayerId>());
}
