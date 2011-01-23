#include "ClientStateMachine.h"

#include "ServerConfiguringState.h"

#include <QVariant>

ClientStateMachine::ClientStateMachine(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  playerId(PlayerId::NONE),
  configuring(new ServerConfiguringState(component, this, "Configuring")) {

  setProperty("playerId", qVariantFromValue(playerId));

  setInitialState(configuring);
}

ClientStateMachine::~ClientStateMachine() {
  delete configuring;
}
