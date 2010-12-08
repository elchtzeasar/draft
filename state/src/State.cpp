#include "State.h"

State::State(QObject* component, State* parent, const char* name) :
    QState(parent),
    name(name) {
  assignProperty(component, "activeState", name);
}
