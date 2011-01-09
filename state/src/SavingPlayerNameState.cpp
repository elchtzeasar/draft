#include "SavingPlayerNameState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "Message.h"
#include "PlayerNameCfgMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <cassert>
#include <iostream>

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

  std::cout << "SavingPlayerNameState: Received player name: " << playerNameCfgMessage.getPlayerName() << std::endl;
}
