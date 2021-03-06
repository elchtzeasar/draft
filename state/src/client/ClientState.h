#ifndef CLIENT_STATE_H_
#define CLIENT_STATE_H_

#include "State.h"

#include <QObject>
#include <QVariant>

#include <glog/logging.h>

class ClientState : public State {
  Q_OBJECT

 public:
  ClientState(QObject* component, State* parent, const char* name);
  virtual ~ClientState();

 private:
  ClientState(const ClientState&);
  ClientState& operator=(ClientState&);

  QVariant playerId;
  State* waitingForConnection;
  State* configuring;
};

#endif // CLIENT_STATE_H
