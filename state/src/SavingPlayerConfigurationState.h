#ifndef SAVING_PLAYER_CONFIGURATION_STATE_H_
#define SAVING_PLAYER_CONFIGURATION_STATE_H_

#include "State.h"

#include <QObject>

class AddressedMessage;
class PlayerId;

class QString;

class SavingPlayerConfigurationState : public State {
  Q_OBJECT

 public:
  SavingPlayerConfigurationState(QObject* component, State* parent);
  virtual ~SavingPlayerConfigurationState();

  virtual void onEntry(QEvent* event);
  
 signals:
  void playerConnected(const PlayerId& playerId, const QString& playerName);
  void sendData(const AddressedMessage& message);

 private:
  SavingPlayerConfigurationState(const SavingPlayerConfigurationState&);
  SavingPlayerConfigurationState& operator=(SavingPlayerConfigurationState&);
};

#endif
