#include "State.h"

#include <QString>
#include <QVariant>

State::State(QObject* stateMachineComponent, State* parent, const char* name, bool assignName) :
    QState(parent),
    parent(*parent),
    name(name),
    nameVariant(this->name) {
  if (parent != 0) {
    this->name.prepend(parent->getName() + "::");
  }

  if (assignName)
    assignProperty(stateMachineComponent, "activeState", this->name);

  connect( this, SIGNAL(entered()),
	   stateMachineComponent, SIGNAL(stateChanged()) );
}

const QString& State::getName() const {
  return name;
}

QVariant State::findProperty(const char* name) const {
  QVariant ownProperty = property(name);

  if (ownProperty.isValid())
    return ownProperty;

  return parent.findProperty(name);
}

bool State::findAndSetProperty(const char* name, const QVariant& value) {
  QVariant ownProperty = property(name);

  if (ownProperty.isValid())
    return setProperty(name, value);

  return parent.findAndSetProperty(name, value);
}
