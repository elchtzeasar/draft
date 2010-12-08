#ifndef CLIENT_STATE_H_
#define CLIENT_STATE_H_

#include "State.h"

class QObject;

class ClientState : public State {
 public:
  ClientState(QObject* component, State* parent, const char* name);
  virtual ~ClientState();

 private:
  ClientState(const ClientState&);
  ClientState& operator=(ClientState&);

  State* chooseClientOrServer;
  State* requestingName;
};

#endif // CLIENT_STATE_H
