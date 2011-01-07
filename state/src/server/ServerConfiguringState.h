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

  State* receivingClientName;
  State* requestingName;
  State* sendingName;
  State* waitingForAllPlayersToConnect;
};

#endif // SERVER_CONFIGURATION_STATE_H
