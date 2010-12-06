#include "StateMachineComponentTest.h"

#include <QSignalSpy>

#include <iostream>

StateMachineComponentTest::StateMachineComponentTest() {
  connect( this, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   &stateMachine, SIGNAL(connectToDraft(const QString&, unsigned int)) );
  stateMachine.start();
}

StateMachineComponentTest::~StateMachineComponentTest() {
}

TEST_F(StateMachineComponentTest, shouldEmitConfigurationRequestAfterConnectToDraft) {
  QSignalSpy configurationRequestSpy(&stateMachine, SIGNAL(configurationRequest()));
  QSignalSpy connectToDraftSpy(&stateMachine, SIGNAL(connectToDraft(const QString&, unsigned int)));

  std::cout << "number of connectToDrafts sent: " << connectToDraftSpy.count() << std::endl;
  const QString host("failHost!!!");
  unsigned int port(666);
  emit connectToDraft(host, port);

  std::cout << "number of connectToDrafts sent  after connectToDraft emitted: "
	    << connectToDraftSpy.count() << std::endl;

  ASSERT_EQ(1, configurationRequestSpy.count());
}
