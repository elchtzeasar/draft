#ifndef CLIENT_STATE_MACHINE_H_
#define CLIENT_STATE_MACHINE_H_

#include "State.h"

class ClientStateMachine : public State {
 public:
  ClientStateMachine(QObject* component, State* parent, const char* name);
  virtual ~ClientStateMachine();

 private:
  ClientStateMachine(const ClientStateMachine&);
  ClientStateMachine& operator=(ClientStateMachine&);

  State* configuring;
};
#endif // CLIENT_STATE_MACHINE_H_
