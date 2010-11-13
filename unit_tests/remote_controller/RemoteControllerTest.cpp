#include "RemoteController.h"

#include <QSignalSpy>

#include <gtest/gtest.h>

#include <sstream>

using std::ostringstream;
using std::stringstream;
using std::endl;

class RemoteControllerTest : public testing::Test {
public:
  RemoteControllerTest() : remoteController(outputStream, inputStream) {}
  ~RemoteControllerTest() {}
protected:
  RemoteController remoteController;
  
  ostringstream outputStream;
  stringstream inputStream;
};

TEST_F(RemoteControllerTest, shouldSendHostDraftSignalWhenHostDraftReceived) {
  inputStream << "host_draft" << endl;
  inputStream << "exit" << endl;

  QSignalSpy spy(&remoteController, SIGNAL(hostDraftSignal(unsigned int)));

  remoteController.run();

  ASSERT_EQ(1, spy.count());
}

TEST_F(RemoteControllerTest, shouldSendConnectToDraftSignalWhenConnectToDraftReceived) {
  inputStream << "connect_to_draft" << endl;
  inputStream << "exit" << endl;

  QSignalSpy spy(&remoteController, SIGNAL(connectToDraftSignal(unsigned int)));

  remoteController.run();

  ASSERT_EQ(1, spy.count());
}
