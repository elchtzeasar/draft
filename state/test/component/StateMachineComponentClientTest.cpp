#include "AddressedMessage.h"
#include "AddressHeader.h"
#include "NullMessage.h"
#include "MessageRouter.h"
#include "PlayerId.h"
#include "PlayerNameCfgMessage.h"
#include "StateMachineComponent.h"
#include "StateMachineComponentWrapper.h"

#include "mock-log.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <string>
#include <sstream>

using ::google::glog_testing::ScopedMockLog;
using testing::_;
using testing::AnyNumber;
using testing::HasSubstr;
using testing::Return;
using std::string;
using std::stringstream;

class StateMachineComponentClientTest : public testing::Test {
 public:
  StateMachineComponentClientTest();

 protected:
  const PlayerId serverPlayerId;
  const PlayerId playerId;
  MessageRouter messageRouter;
  StateMachineComponent stateMachineComponent;
  StateMachineComponentWrapper stateMachineComponentWrapper;

  const AddressedMessage addressedPlayerIdCfg;

  void startComponentAndWait();
  void connectToDraftAndWait();
  void sendPlayerIdAndWait();
};

void StateMachineComponentClientTest::startComponentAndWait() {
  stateMachineComponentWrapper.startComponent();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForStateChange());
}

void StateMachineComponentClientTest::connectToDraftAndWait() {
  stateMachineComponentWrapper.sendConnectToDraft();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForStateChange());

  stateMachineComponentWrapper.sendConnectedToDraft();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForStateChange());
}

void StateMachineComponentClientTest::sendPlayerIdAndWait() {
  stateMachineComponentWrapper.sendDataReceived(addressedPlayerIdCfg);

  ASSERT_TRUE(stateMachineComponentWrapper.waitForStateChange());
}

StateMachineComponentClientTest::StateMachineComponentClientTest() :
  playerId(5),
  stateMachineComponentWrapper(playerId, stateMachineComponent, messageRouter),
  addressedPlayerIdCfg(new AddressHeader(PlayerId::SERVER, playerId),
		       new NullMessage(MessageNumber::PLAYER_ID_CFG)) {
  messageRouter.registerReceiver(playerId, stateMachineComponentWrapper);
  qRegisterMetaType<AddressedMessage>("AddressedMessage");
  qRegisterMetaType<PlayerId>("PlayerId");
}


TEST_F(StateMachineComponentClientTest, shouldSendPlayerIdCnfWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerIdCnf(new AddressHeader(playerId, PlayerId::SERVER),
				       new NullMessage(MessageNumber::PLAYER_ID_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  stateMachineComponentWrapper.sendDataReceived(addressedPlayerIdCfg);

  ASSERT_TRUE(stateMachineComponentWrapper.waitForSendData(expectedPlayerIdCnf));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCfgWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerNameCfg(new AddressHeader(playerId, PlayerId::SERVER),
					 new PlayerNameCfgMessage(stateMachineComponentWrapper.getPlayerName().c_str()));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForSendData(expectedPlayerNameCfg));
}
