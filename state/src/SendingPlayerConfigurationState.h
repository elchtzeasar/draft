#ifndef SENDING_PLAYER_CONFIGURATION_STATE_H_
#define SENDING_PLAYER_CONFIGURATION_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;

class SendingPlayerConfigurationState : public State {
  Q_OBJECT

 public:
  SendingPlayerConfigurationState(QObject* component, State* parent);
  virtual ~SendingPlayerConfigurationState();
  
  virtual void onEntry(QEvent* event);
  
 signals:
  void sendData(const AddressedMessage& message);

 private:
  SendingPlayerConfigurationState(const SendingPlayerConfigurationState&);
  SendingPlayerConfigurationState& operator=(SendingPlayerConfigurationState&);
};

#endif
