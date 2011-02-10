#ifndef RECEIVED_MESSAGE_TRANSITION_H_
#define RECEIVED_MESSAGE_TRANSITION_H_

#include "MessageNumber.h"

#include <QSignalTransition>

class QObject;

class ReceivedMessageTransition : public QSignalTransition
 {
 public:
   ReceivedMessageTransition(QObject* sender,
			     QState* sourceState, QState* targetState,
			     const MessageNumber& expectedMessageNumber);

 protected:
   bool eventTest(QEvent *e);

 private:
   MessageNumber expectedMessageNumber;
 };

#endif // RECEIVED_MESSAGE_TRANSITION_H_
