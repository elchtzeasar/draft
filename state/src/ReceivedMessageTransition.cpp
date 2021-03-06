#include "ReceivedMessageTransition.h"

#include "AddressedMessage.h"
#include "Message.h"

#include <QStateMachine>
#include <QEvent>

#include <glog/logging.h>

ReceivedMessageTransition::ReceivedMessageTransition(QObject* sender,
						     QState* sourceState,
						     QState* targetState,
						     const MessageNumber& expectedMessageNumber)
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
    LOG(ERROR) << "ReceivedMessageTransition::eventTest(): "
	 << "cannot convert to AddressedMessage...";
    return false;
  }

  const AddressedMessage& message = qVariant.value<AddressedMessage>();

  if (message.getMessage().getMessageNumber() == expectedMessageNumber) {
    return true;
  } else {
    LOG(ERROR) << "ReceivedMessageTransition::eventTest(): "
	 << "recevied wrong message number: " << message.getMessage().getMessageNumber()
	 << ", expected: " << expectedMessageNumber;
  return false;
  }

}
