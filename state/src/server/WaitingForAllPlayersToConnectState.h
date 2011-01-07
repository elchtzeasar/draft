#ifndef WAITING_FOR_ALL_PLAYERS_TO_CONNECT_STATE_H_
#define WAITING_FOR_ALL_PLAYERS_TO_CONNECT_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;

class WaitingForAllPlayersToConnectState : public State {
  Q_OBJECT

 public:
  WaitingForAllPlayersToConnectState(QObject* component, State* parent);
  virtual ~WaitingForAllPlayersToConnectState();
  
  virtual void onEntry(QEvent* event);
  
 signals:
  void sendData(const AddressedMessage& message);

 private:
  WaitingForAllPlayersToConnectState(const WaitingForAllPlayersToConnectState&);
  WaitingForAllPlayersToConnectState& operator=(WaitingForAllPlayersToConnectState&);
};

#endif // WAITING_FOR_ALL_PLAYERS_TO_CONNECT_STATE_H_
