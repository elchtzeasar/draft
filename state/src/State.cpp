#include "State.h"

State::State(QObject* component, State* parent, const char* name, bool assignName) :
    QState(parent),
    name(name),
    nameVariant(this->name) {
  if (parent != 0) {
    this->name.prepend(parent->getName() + "::");
  }

  if (assignName)
    assignProperty(component, "activeState", this->name);
}

const QString& State::getName() const {
  return name;
}
