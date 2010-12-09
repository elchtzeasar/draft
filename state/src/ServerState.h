#ifndef SERVER_STATE_H_
#define SERVER_STATE_H_

#include "State.h"

class QObject;

class ServerState : public State {
 public:
  ServerState(QObject* component, State* parent, const char* name);
  virtual ~ServerState();

 private:
  ServerState(const ServerState&);
  ServerState& operator=(ServerState&);

  State* listeningForConnections;
  State* clientStateMachine;
};

#endif // SERVER_STATE_H
