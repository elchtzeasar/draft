#include "ServerConfiguringState.h"

#include "Message.h"
#include "PlayerId.h"
#include "ReceivedMessageTransition.h"
#include "SendingPlayerIdState.h"
#include "SendingPlayerConfigurationState.h"
#include "SavingPlayerConfigurationState.h"

#include <QVariant>

class AddressedMessage;

ServerConfiguringState::ServerConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  sendingPlayerId(new SendingPlayerIdState(component, this)),
  receivingClientName(new State(component, this, "ReceivingClientName")),
  savingPlayerName(new SavingPlayerConfigurationState(component, this)),
  waitingForOtherPlayers(new State(component, this, "WaitingForOtherPlayers")) {

  connect(this, SIGNAL(configurationRequest(const PlayerId&)),
	  component, SIGNAL(configurationRequest(const PlayerId&)));
  connect(savingPlayerName, SIGNAL(playerConnected(const PlayerId&, const QString&)),
	  component, SIGNAL(playerConnected(const PlayerId&, const QString&)) );

  new ReceivedMessageTransition(
    component, sendingPlayerId, receivingClientName, MessageNumber::PLAYER_ID_CNF);
  new ReceivedMessageTransition(
    component, receivingClientName, savingPlayerName, MessageNumber::PLAYER_CONFIGURATION_CFG);
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
