#ifndef CLIENT_CONFIGURATION_STATE_H_
#define CLIENT_CONFIGURATION_STATE_H_

#include "State.h"

class QObject;

class ClientConfiguringState : public State {
 public:
  ClientConfiguringState(QObject* component, State* parent, const char* name);
  virtual ~ClientConfiguringState();

 private:
  ClientConfiguringState(const ClientConfiguringState&);
  ClientConfiguringState& operator=(ClientConfiguringState&);

  State* requestingName;
  State* sendingName;
};

#endif // CLIENT_CONFIGURATION_STATE_H
