#ifndef SENDING_NAME_STATE_H_
#define SENDING_NAME_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;

class SendingNameState : public State {
  Q_OBJECT

 public:
  SendingNameState(QObject* component, State* parent);
  virtual ~SendingNameState();
  
  virtual void onEntry(QEvent* event);
  
 signals:
  void sendData(const AddressedMessage& message);

 private:
  SendingNameState(const SendingNameState&);
  SendingNameState& operator=(SendingNameState&);
};

#endif // SENDING_NAME_STATE_H_