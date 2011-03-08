#include "SendingPlayerConfigurationState.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "PlayerId.h"
#include "PlayerConfigurationCfgMessage.h"

#include <QEvent>
#include <QSignalTransition>
#include <QStateMachine>

#include <cassert>

SendingPlayerConfigurationState::SendingPlayerConfigurationState(QObject* component, State* parent) : 
  State(component, parent, "SendingName") {
}

SendingPlayerConfigurationState::~SendingPlayerConfigurationState() {}

void SendingPlayerConfigurationState::onEntry(QEvent* event) {
  assert(event->type() == QEvent::StateMachineSignal &&
	 "SendingPlayerConfigurationState should only be entered with a QEvent::StateMachineSignal");
  QStateMachine::SignalEvent* signalEvent(static_cast<QStateMachine::SignalEvent*>(event));

  const PlayerId& playerId = signalEvent->arguments().at(0).value<PlayerId>();
  const QString playerName = signalEvent->arguments().at(1).toString();

  AddressHeader* addressHeader = new AddressHeader(playerId, PlayerId::SERVER);
  PlayerConfigurationCfgMessage* playerNameCfg = new PlayerConfigurationCfgMessage(playerName.toStdString().c_str());
  emit sendData(AddressedMessage(addressHeader, playerNameCfg));
}
