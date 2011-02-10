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
  const PlayerId ownPlayerId;
  const PlayerId otherPlayerId;
  MessageRouter messageRouter;
  StateMachineComponent stateMachineComponent;
  StateMachineComponentWrapper stateMachineComponentWrapper;

  const AddressedMessage addressedPlayerIdCfg;

  void startComponentAndWait();
  void connectToDraftAndWait();
  void sendPlayerIdAndWait();
  void sendPlayerNameAndWait();
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

void StateMachineComponentClientTest::sendPlayerNameAndWait() {
  const AddressedMessage playerNameCfg(new AddressHeader(otherPlayerId, ownPlayerId),
				       new PlayerNameCfgMessage("Other player"));

  stateMachineComponentWrapper.sendDataReceived(playerNameCfg);

  ASSERT_TRUE(stateMachineComponentWrapper.waitForStateChange());
}

StateMachineComponentClientTest::StateMachineComponentClientTest() :
  ownPlayerId(5), otherPlayerId(6),
  stateMachineComponentWrapper(ownPlayerId, stateMachineComponent, messageRouter),
  addressedPlayerIdCfg(new AddressHeader(PlayerId::SERVER, ownPlayerId),
		       new NullMessage(MessageNumber::PLAYER_ID_CFG)) {
  messageRouter.registerReceiver(ownPlayerId, stateMachineComponentWrapper);

  qRegisterMetaType<AddressedMessage>("AddressedMessage");
  qRegisterMetaType<PlayerId>("PlayerId");
}


TEST_F(StateMachineComponentClientTest, shouldSendPlayerIdCnfWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerIdCnf(new AddressHeader(ownPlayerId, PlayerId::SERVER),
				       new NullMessage(MessageNumber::PLAYER_ID_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForSendData(expectedPlayerIdCnf));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCfgWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerNameCfg(new AddressHeader(ownPlayerId, PlayerId::SERVER),
					 new PlayerNameCfgMessage(stateMachineComponentWrapper.getPlayerName().c_str()));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForSendData(expectedPlayerNameCfg));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCnfWhenConnectedToDraftAndPlayerNameCfgReceived) {
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(ownPlayerId, otherPlayerId),
					 new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  sendPlayerNameAndWait();

  ASSERT_TRUE(stateMachineComponentWrapper.waitForSendData(expectedPlayerNameCnf));
}
