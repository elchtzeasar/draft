#include "SavingPlayerNameState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"
#include "PlayerNameCfgMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <glog/logging.h>

#include <cassert>

SavingPlayerNameState::SavingPlayerNameState(QObject* component, State* parent) : 
  State(component, parent, "SavingPlayerName") {
}

SavingPlayerNameState::~SavingPlayerNameState() {}

void SavingPlayerNameState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SavingPlayerNameState should only be entered with a QEvent::StateMachineSignal");

  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));
  const QVariant& qVariant(signalEvent->arguments().at(0));
  assert(qVariant.canConvert<AddressedMessage>() && 
  	 "Must be able to convert argument to AddressedMessage!");
  const AddressedMessage& message = qVariant.value<AddressedMessage>();

  const PlayerNameCfgMessage& playerNameCfgMessage(message.getMessage().to<PlayerNameCfgMessage>());

  AddressHeader* addressHeader = new AddressHeader;
  NullMessage* playerNameCnf = new NullMessage(MessageNumber::PLAYER_NAME_CNF);
  emit sendData(AddressedMessage(addressHeader, playerNameCnf));

  LOG(INFO) << "SavingPlayerNameState: Received player name: " << playerNameCfgMessage.getPlayerName();
}
