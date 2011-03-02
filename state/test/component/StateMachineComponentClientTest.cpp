#include "AddressedMessage.h"
#include "AddressHeader.h"
#include "ConfigurationComponentStub.h"
#include "DraftApplication.h"
#include "NetworkComponentStub.h"
#include "NullMessage.h"
#include "PlayerId.h"
#include "RemoteControllerStub.h"
#include "PlayerNameCfgMessage.h"
#include "StateChangeWaiter.h"
#include "StateMachineComponent.h"

#include "mock-log.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <QCoreApplication>
#include <string>
#include <sstream>

using ::google::glog_testing::ScopedMockLog;
using testing::_;
using testing::AnyNumber;
using testing::HasSubstr;
using testing::Return;
using std::string;
using std::stringstream;

static const QString SOME_STRING("some string");
static const int DONT_CARE(0);

class StateMachineComponentClientTest : public testing::Test {
 public:
  StateMachineComponentClientTest();

 protected:
  const PlayerId serverPlayerId;
  const PlayerId ownPlayerId;
  const PlayerId otherPlayerId;
  QCoreApplication* application;
  RemoteControllerStub remoteController;
  ConfigurationComponentStub configurationComponent;
  NetworkComponentStub networkComponent;
  StateMachineComponent stateMachineComponent;
  DraftApplication draftApplication;

  StateChangeWaiter stateChangeWaiter;

  void startComponentAndWait();
  void connectToDraftAndWait();
  void sendPlayerIdAndWait();
  void confirmPlayerNameAndWait();
  void sendPlayerNameAndWait();
};

StateMachineComponentClientTest::StateMachineComponentClientTest() :
  ownPlayerId(5), otherPlayerId(6),
  application(QCoreApplication::instance()),
  draftApplication(*application, remoteController, configurationComponent,
		   networkComponent, stateMachineComponent),
  stateChangeWaiter(stateMachineComponent) {
    qRegisterMetaType<AddressedMessage>("AddressedMessage");
    qRegisterMetaType<PlayerId>("PlayerId");

    draftApplication.connectSlotsToSignals();
}

void StateMachineComponentClientTest::startComponentAndWait() {
  stateMachineComponent.start();

  ASSERT_TRUE(stateChangeWaiter.wait("ChooseClientOrServer"));
}

void StateMachineComponentClientTest::connectToDraftAndWait() {
  remoteController.sendConnectToDraft(SOME_STRING, DONT_CARE);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::WaitingForConnection"));

  networkComponent.sendConnectedToDraft();

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::ReceivingPlayerId"));
}

void StateMachineComponentClientTest::sendPlayerIdAndWait() {
  const AddressedMessage addressedPlayerIdCfg(
      new AddressHeader(PlayerId::SERVER, ownPlayerId),
      new NullMessage(MessageNumber::PLAYER_ID_CFG));

  networkComponent.sendDataReceived(addressedPlayerIdCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::SavingPlayerId"));
}

void StateMachineComponentClientTest::confirmPlayerNameAndWait() {
  const AddressedMessage playerNameCnf(new AddressHeader(PlayerId::SERVER, ownPlayerId),
				       new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  networkComponent.sendDataReceived(playerNameCnf);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::ReceivingPlayerName"));
}

void StateMachineComponentClientTest::sendPlayerNameAndWait() {
  const AddressedMessage playerNameCfg(new AddressHeader(otherPlayerId, ownPlayerId),
				       new PlayerNameCfgMessage("Other player"));

  networkComponent.sendDataReceived(playerNameCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::SavingPlayerName"));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerIdCnfWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerIdCnf(new AddressHeader(ownPlayerId, PlayerId::SERVER),
				       new NullMessage(MessageNumber::PLAYER_ID_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerIdCnf));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCfgWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerNameCfg(new AddressHeader(ownPlayerId, PlayerId::SERVER),
                                         new PlayerNameCfgMessage(configurationComponent.getPlayerName(ownPlayerId).c_str()));
  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  confirmPlayerNameAndWait();

  LOG(INFO) << "Expected message: " << expectedPlayerNameCfg;
  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCfg));
}
 
TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCnfWhenConnectedToDraftAndPlayerNameCfgReceived) {
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(ownPlayerId, otherPlayerId),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  confirmPlayerNameAndWait();
  sendPlayerNameAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCnf));
}
