#include "SendingNameState.h"

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
  const QString playerName = signalEvent->arguments().at(0).toString();

  emit sendData(playerName);
}
