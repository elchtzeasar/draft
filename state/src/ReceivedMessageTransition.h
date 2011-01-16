#ifndef RECEIVED_MESSAGE_TRANSITION_H_
#define RECEIVED_MESSAGE_TRANSITION_H_

#include <QSignalTransition>

class QObject;

class ReceivedMessageTransition : public QSignalTransition
 {
 public:
   ReceivedMessageTransition(QObject* sender,
			     QState* sourceState, QState* targetState,
			     quint16 expectedMessageNumber);

 protected:
   bool eventTest(QEvent *e);

 private:
   quint16 expectedMessageNumber;
 };

#endif // RECEIVED_MESSAGE_TRANSITION_H_
