#include "ClientConfiguringState.h"

#include "Message.h"
#include "PlayerId.h"
#include "ReceivedMessageTransition.h"
#include "SavingPlayerIdState.h"
#include "SavingPlayerConfigurationState.h"
#include "SendingPlayerConfigurationState.h"

#include <QVariant>

class AddressedMessage;

ClientConfiguringState::ClientConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  receivingPlayerId(new State(component, this, "ReceivingPlayerId")),
  savingPlayerId(new SavingPlayerIdState(component, this)),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingPlayerConfigurationState(component, this)),
  receivingPlayerName(new State(component, this, "ReceivingPlayerName")),
  savingPlayerName(new SavingPlayerConfigurationState(component, this)) {

  connect(savingPlayerId, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(savingPlayerName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(receivingPlayerName, SIGNAL(entered()),
          component, SIGNAL(connectedToServer()));
  connect(savingPlayerName, SIGNAL(playerConnected(const PlayerId&, const QString&)),
	  component, SIGNAL(playerConnected(const PlayerId&, const QString&)) );

  connect(savingPlayerId, SIGNAL(setOwnPlayerId(const PlayerId&)),
	  component, SIGNAL(setOwnPlayerId(const PlayerId&)) );
  connect(requestingName, SIGNAL(entered()), this, SLOT(sendConfigurationRequest()));
  connect(this, SIGNAL(configurationRequest(const PlayerId&)),
	  component, SIGNAL(configurationRequest(const PlayerId&)));

  new ReceivedMessageTransition(
    component, receivingPlayerId, savingPlayerId, MessageNumber::PLAYER_ID_CFG);
  savingPlayerId->addTransition(requestingName);

  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const PlayerId&, const QString)), sendingName);

  new ReceivedMessageTransition(
    component, sendingName, receivingPlayerName, MessageNumber::PLAYER_CONFIGURATION_CNF);

  new ReceivedMessageTransition(
    component, receivingPlayerName, savingPlayerName, MessageNumber::PLAYER_CONFIGURATION_CFG);

  savingPlayerName->addTransition(receivingPlayerName);

  setInitialState(receivingPlayerId);
}

ClientConfiguringState::~ClientConfiguringState() {
  delete receivingPlayerId;
  delete savingPlayerId;
  delete requestingName;
  delete sendingName;
  delete receivingPlayerName;
  delete savingPlayerName;
}

void ClientConfiguringState::sendConfigurationRequest() {
  emit configurationRequest(findProperty("playerId").value<PlayerId>());
}
