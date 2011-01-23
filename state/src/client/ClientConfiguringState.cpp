#include "ClientConfiguringState.h"

#include "Message.h"
#include "PlayerId.h"
#include "ReceivedMessageTransition.h"
#include "SavingPlayerIdState.h"
#include "SendingNameState.h"

#include <QVariant>

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
  connect(savingPlayerId, SIGNAL(setOwnPlayerId(const PlayerId&)),
	  component, SIGNAL(setOwnPlayerId(const PlayerId&)) );
  connect(requestingName, SIGNAL(entered()), this, SLOT(sendConfigurationRequest()));
  connect(sendingName, SIGNAL(sendData(const AddressedMessage&)),
	  component, SIGNAL(sendData(const AddressedMessage&)) );
  connect(this, SIGNAL(configurationRequest(const PlayerId&)),
	  component, SIGNAL(configurationRequest(const PlayerId&)));

  new ReceivedMessageTransition(
    component, receivingPlayerId, savingPlayerId, PLAYER_ID_CFG);
  savingPlayerId->addTransition(requestingName);
  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const PlayerId&, const QString)), sendingName);

  sendingName->addTransition(receivingPlayerName);

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
  emit configurationRequest(findProperty("playerId").value<PlayerId>());
}
