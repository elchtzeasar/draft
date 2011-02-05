#include "SavingPlayerIdState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <cassert>

SavingPlayerIdState::SavingPlayerIdState(QObject* component, State* parent) : 
  State(component, parent, "SavingPlayerId") {
}

SavingPlayerIdState::~SavingPlayerIdState() {}

void SavingPlayerIdState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SavingPlayerIdState should only be entered with a QEvent::StateMachineSignal");

  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));
  const QVariant& qVariant(signalEvent->arguments().at(0));
  assert(qVariant.canConvert<AddressedMessage>() && 
  	 "Must be able to convert argument to AddressedMessage!");
  const AddressedMessage& message = qVariant.value<AddressedMessage>();
  const PlayerId& ownPlayerId(message.getHeader().getReceiverPlayerId());
  const PlayerId& senderPlayerId(message.getHeader().getSenderPlayerId());

  findAndSetProperty("playerId", qVariantFromValue(ownPlayerId));
  emit setOwnPlayerId(ownPlayerId);

  AddressHeader* addressHeader = new AddressHeader(ownPlayerId, senderPlayerId);
  NullMessage* playerIdCnf = new NullMessage(PLAYER_ID_CNF);
  emit sendData(AddressedMessage(addressHeader, playerIdCnf));
}
