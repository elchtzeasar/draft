#ifndef SERVER_CONFIGURATION_STATE_H_
#define SERVER_CONFIGURATION_STATE_H_

#include "State.h"

class QObject;

class ServerConfiguringState : public State {
 public:
  ServerConfiguringState(QObject* component, State* parent, const char* name);
  virtual ~ServerConfiguringState();

 private:
  ServerConfiguringState(const ServerConfiguringState&);
  ServerConfiguringState& operator=(ServerConfiguringState&);

  State* sendingPlayerId;
  State* receivingClientName;
  State* savingPlayerName;
  State* requestingName;
  State* sendingName;
};

#endif // SERVER_CONFIGURATION_STATE_H
