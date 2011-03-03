#ifndef SAVING_PLAYER_NAME_STATE_H_
#define SAVING_PLAYER_NAME_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;
class PlayerId;

class QString;

class SavingPlayerNameState : public State {
  Q_OBJECT

 public:
  SavingPlayerNameState(QObject* component, State* parent);
  virtual ~SavingPlayerNameState();

  virtual void onEntry(QEvent* event);
  
 signals:
  void playerConnected(const PlayerId& playerId, const QString& playerName);
  void sendData(const AddressedMessage& message);

 private:
  SavingPlayerNameState(const SavingPlayerNameState&);
  SavingPlayerNameState& operator=(SavingPlayerNameState&);
};

#endif // SAVING_PLAYER_NAME_STATE_H_
