#include "SavingPlayerConfigurationState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"
#include "PlayerConfigurationCfgMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <glog/logging.h>

#include <cassert>

SavingPlayerConfigurationState::SavingPlayerConfigurationState(QObject* component, State* parent) : 
  State(component, parent, "SavingPlayerName") {
}

SavingPlayerConfigurationState::~SavingPlayerConfigurationState() {}

void SavingPlayerConfigurationState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SavingPlayerConfigurationState should only be entered with a QEvent::StateMachineSignal");

  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));
  const QVariant& qVariant(signalEvent->arguments().at(0));
  assert(qVariant.canConvert<AddressedMessage>() && 
  	 "Must be able to convert argument to AddressedMessage!");
  const AddressedMessage& message = qVariant.value<AddressedMessage>();

  const PlayerConfigurationCfgMessage& playerNameCfgMessage(message.getMessage().to<PlayerConfigurationCfgMessage>());

  const PlayerId& ownPlayerId(message.getHeader().getReceiverPlayerId());
  const PlayerId& senderPlayerId(message.getHeader().getSenderPlayerId());
  const QString& playerName = playerNameCfgMessage.getPlayerName();

  AddressHeader* addressHeader = new AddressHeader(ownPlayerId, senderPlayerId);
  NullMessage* playerNameCnf = new NullMessage(MessageNumber::PLAYER_CONFIGURATION_CNF);

  emit playerConnected(senderPlayerId, playerName);
  emit sendData(AddressedMessage(addressHeader, playerNameCnf));

  LOG(INFO) << "Received player name: " << playerNameCfgMessage.getPlayerName();
}
