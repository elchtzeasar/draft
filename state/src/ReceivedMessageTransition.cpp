#include "ReceivedMessageTransition.h"

#include "AddressedMessage.h"
#include "Message.h"

#include <QStateMachine>
#include <QEvent>

#include <iostream>

using std::cerr;
using std::endl;

ReceivedMessageTransition::ReceivedMessageTransition(QObject* sender,
						     QState* sourceState,
						     QState* targetState,
						     quint16 expectedMessageNumber)
  : QSignalTransition(sender, SIGNAL(dataReceived(const AddressedMessage&)), sourceState),
    expectedMessageNumber(expectedMessageNumber)
{
  setTargetState(targetState);
}

bool ReceivedMessageTransition::eventTest(QEvent* event) {
  if (!QSignalTransition::eventTest(event)) {
    return false;
  }

  QStateMachine::SignalEvent* signalEvent = static_cast<QStateMachine::SignalEvent*>(event);
  const QVariant& qVariant(signalEvent->arguments().at(0));
  if (!qVariant.canConvert<AddressedMessage>()) {
    cerr << "ReceivedMessageTransition::eventTest(): "
	 << "cannot convert to AddressedMessage..." << endl;
    return false;
  }

  const AddressedMessage& message = qVariant.value<AddressedMessage>();

  if (message.getMessage().getMessageNumber() == expectedMessageNumber) {
    return true;
  } else {
    cerr << "ReceivedMessageTransition::eventTest(): "
	 << "recevied wrong message number: " << int(message.getMessage().getMessageNumber())
	 << ", expected: " << int(expectedMessageNumber) << endl;
  return false;
  }

}