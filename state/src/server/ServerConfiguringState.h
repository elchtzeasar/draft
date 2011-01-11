#ifndef SERVER_CONFIGURATION_STATE_H_
#define SERVER_CONFIGURATION_STATE_H_

#include "State.h"

#include <QObject>

class ServerConfiguringState : public State {
  Q_OBJECT

 public:
  ServerConfiguringState(QObject* component, State* parent, const char* name);
  virtual ~ServerConfiguringState();

 signals:
  void configurationRequest(quint8 playerId);

 private slots:
  void sendConfigurationRequest();

 private:
  ServerConfiguringState(const ServerConfiguringState&);
  ServerConfiguringState& operator=(ServerConfiguringState&);

  State* sendingPlayerId;
  State* receivingClientName;
  State* savingPlayerName;
  State* waitingForOtherPlayers;
};

#endif // SERVER_CONFIGURATION_STATE_H
