#include "SendingPlayerIdState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "NullMessage.h"
#include "PlayerIdCfgMessage.h"

#include <QEvent>
#include <QStateMachine>

#include <cassert>
#include <iostream>

SendingPlayerIdState::SendingPlayerIdState(QObject* component, State* parent) : 
  State(component, parent, "SendingPlayerId") {
}

SendingPlayerIdState::~SendingPlayerIdState() {}

void SendingPlayerIdState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SendingPlayerIdState should only be entered with a QEvent::StateMachineSignal");

  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));
  const QVariant& playerIdVariant(signalEvent->arguments().at(0));
  assert(playerIdVariant.canConvert<quint8>() && 
  	 "Must be able to convert argument to quint8!");
  const quint8 playerId = playerIdVariant.value<quint8>();

  // Set playerId in "root" State (currently ClientStateMachine):
  findAndSetProperty("playerId", playerIdVariant);

  // Send playerId to client:
  AddressHeader* addressHeader = new AddressHeader;
  NullMessage* playerNameCfg = new NullMessage(PLAYER_ID_CFG);
  emit sendData(AddressedMessage(addressHeader, playerNameCfg));
}