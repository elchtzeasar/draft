#include "StateMachineComponentStub.h"

#include <glog/logging.h>

StateMachineComponentStub::StateMachineComponentStub() : activeState("Init") {}
StateMachineComponentStub::~StateMachineComponentStub() {}

const QString StateMachineComponentStub::getActiveState() const {
  return activeState;
}

void StateMachineComponentStub::setActiveState(QString newState) {
  LOG(INFO) << "StateMachineComponent: STATE CHANGE " << activeState.toStdString().c_str()
	    << " -> " << newState.toStdString().c_str();
  activeState = newState;
}
