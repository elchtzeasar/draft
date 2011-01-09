#include "ClientStateMachine.h"

#include "ServerConfiguringState.h"

#include <QVariant>

ClientStateMachine::ClientStateMachine(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  playerId(0xff),
  configuring(new ServerConfiguringState(component, this, "Configuring")) {

  setProperty("playerId", playerId);

  setInitialState(configuring);
}

ClientStateMachine::~ClientStateMachine() {
  delete configuring;
}
