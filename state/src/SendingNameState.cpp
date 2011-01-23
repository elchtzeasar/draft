#include "SendingNameState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "PlayerId.h"
#include "PlayerNameCfgMessage.h"

#include <QEvent>
#include <QSignalTransition>
#include <QStateMachine>

#include <cassert>

SendingNameState::SendingNameState(QObject* component, State* parent) : 
  State(component, parent, "SendingName") {
}

SendingNameState::~SendingNameState() {}

void SendingNameState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SendingNameState should only be entered with a QEvent::StateMachineSignal");
  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));

  const PlayerId& playerId = signalEvent->arguments().at(0).value<PlayerId>();
  const QString playerName = signalEvent->arguments().at(1).toString();

  AddressHeader* addressHeader = new AddressHeader(playerId, PlayerId::SERVER);
  PlayerNameCfgMessage* playerNameCfg = new PlayerNameCfgMessage(playerName.toStdString().c_str());
  emit sendData(AddressedMessage(addressHeader, playerNameCfg));
}
