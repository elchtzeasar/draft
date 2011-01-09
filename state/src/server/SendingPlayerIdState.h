#ifndef SENDING_PLAYER_ID_STATE_H_
#define SENDING_PLAYER_ID_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;

class SendingPlayerIdState : public State {
  Q_OBJECT

 public:
  SendingPlayerIdState(QObject* component, State* parent);
  virtual ~SendingPlayerIdState();

  virtual void onEntry(QEvent* event);
  
 signals:
  void sendData(const AddressedMessage& message);

 private:
  SendingPlayerIdState(const SendingPlayerIdState&);
  SendingPlayerIdState& operator=(SendingPlayerIdState&);

  const State* nextState;
};

#endif // SENDING_PLAYER_ID_STATE_H_
