#ifndef SAVING_PLAYER_ID_STATE_H_
#define SAVING_PLAYER_ID_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;

class SavingPlayerIdState : public State {
  Q_OBJECT

 public:
  SavingPlayerIdState(QObject* component, State* parent);
  virtual ~SavingPlayerIdState();

  virtual void onEntry(QEvent* event);
  
 signals:
  void setOwnPlayerId(quint8 playerId);
  void sendData(const AddressedMessage& message);

 private:
  SavingPlayerIdState(const SavingPlayerIdState&);
  SavingPlayerIdState& operator=(SavingPlayerIdState&);

  const State* nextState;
};

#endif // SAVING_PLAYER_ID_STATE_H_
