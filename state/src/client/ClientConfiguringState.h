#ifndef CLIENT_CONFIGURATION_STATE_H_
#define CLIENT_CONFIGURATION_STATE_H_

#include "State.h"

#include <QObject>

class ClientConfiguringState : public State {
  Q_OBJECT

 public:
  ClientConfiguringState(QObject* component, State* parent, const char* name);
  virtual ~ClientConfiguringState();

 signals:
  void configurationRequest(quint8 playerId);

 private slots:
  void sendConfigurationRequest();

 private:
  ClientConfiguringState(const ClientConfiguringState&);
  ClientConfiguringState& operator=(ClientConfiguringState&);

  State* receivingPlayerId;
  State* savingPlayerId;
  State* requestingName;
  State* sendingName;
  State* receivingPlayerList;
};

#endif // CLIENT_CONFIGURATION_STATE_H_
