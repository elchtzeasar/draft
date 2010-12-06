#ifndef STATE_MACHINE_TEST_H_
#define STATE_MACHINE_TEST_H_

#include "StateMachineComponent.h"

#include <QObject>

#include <gtest/gtest.h>

class StateMachineComponentTest : public QObject, public testing::Test {
  Q_OBJECT

 public:
  StateMachineComponentTest();
  virtual ~StateMachineComponentTest();

 signals:
  void connectToDraft(const QString&, unsigned int);
  void configurationRequest();

 protected:
  StateMachineComponent stateMachine;
};

#endif // STATE_MACHINE_TEST_H_
