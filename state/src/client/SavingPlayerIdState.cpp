#include "SavingPlayerIdState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <cassert>
#include <iostream>

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

  std::cout << "SavingPlayerIdState: Received player id: " << -1 << std::endl;

  AddressHeader* addressHeader = new AddressHeader;
  NullMessage* playerNameCnf = new NullMessage(PLAYER_ID_CNF);
  emit sendData(AddressedMessage(addressHeader, playerNameCnf));
}