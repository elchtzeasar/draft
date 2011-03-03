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
#include <QSignalSpy>
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
  static const PlayerId OWN_PLAYER_ID;
  static const PlayerId OTHER_PLAYER_ID;
  static const char* OTHER_PLAYER_NAME;

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

const PlayerId StateMachineComponentClientTest::OWN_PLAYER_ID(5);
const PlayerId StateMachineComponentClientTest::OTHER_PLAYER_ID(6);
const char* StateMachineComponentClientTest::OTHER_PLAYER_NAME("Other player");

StateMachineComponentClientTest::StateMachineComponentClientTest() :
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
      new AddressHeader(PlayerId::SERVER, OWN_PLAYER_ID),
      new NullMessage(MessageNumber::PLAYER_ID_CFG));

  networkComponent.sendDataReceived(addressedPlayerIdCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::SavingPlayerId"));
}

void StateMachineComponentClientTest::confirmPlayerNameAndWait() {
  const AddressedMessage playerNameCnf(new AddressHeader(PlayerId::SERVER, OWN_PLAYER_ID),
				       new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  networkComponent.sendDataReceived(playerNameCnf);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::ReceivingPlayerName"));
}

void StateMachineComponentClientTest::sendPlayerNameAndWait() {
  const AddressedMessage playerNameCfg(new AddressHeader(OTHER_PLAYER_ID, OWN_PLAYER_ID),
				       new PlayerNameCfgMessage(OTHER_PLAYER_NAME));

  networkComponent.sendDataReceived(playerNameCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Client::Configuring::SavingPlayerName"));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerIdCnfWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerIdCnf(new AddressHeader(OWN_PLAYER_ID, PlayerId::SERVER),
				       new NullMessage(MessageNumber::PLAYER_ID_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerIdCnf));
}

TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCfgWhenConnectedToDraftAndPlayerIdCfgReceived) {
  AddressedMessage expectedPlayerNameCfg(new AddressHeader(OWN_PLAYER_ID, PlayerId::SERVER),
                                         new PlayerNameCfgMessage(configurationComponent.getPlayerName(OWN_PLAYER_ID).c_str()));
  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  confirmPlayerNameAndWait();

  LOG(INFO) << "Expected message: " << expectedPlayerNameCfg;
  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCfg));
}
 
TEST_F(StateMachineComponentClientTest, shouldSendPlayerNameCnfWhenConnectedToDraftAndPlayerNameCfgReceived) {
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(OWN_PLAYER_ID, OTHER_PLAYER_ID),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  confirmPlayerNameAndWait();
  sendPlayerNameAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCnf));
}

TEST_F(StateMachineComponentClientTest, shouldEmitPlayerConnectedWhenConnectedToDraftAndPlayerNameCfgReceived) {
  QSignalSpy playerConnectedSpy(&stateMachineComponent,
                                SIGNAL(playerConnected(const PlayerId&, const QString&)));
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(OWN_PLAYER_ID, OTHER_PLAYER_ID),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  connectToDraftAndWait();
  sendPlayerIdAndWait();
  confirmPlayerNameAndWait();
  sendPlayerNameAndWait();

  ASSERT_EQ(1, playerConnectedSpy.count());
  QList<QVariant> arguments = playerConnectedSpy.takeFirst();
  ASSERT_EQ(OTHER_PLAYER_ID, arguments.at(0).value<PlayerId>());
  ASSERT_STREQ(OTHER_PLAYER_NAME, arguments.at(1).toString().toStdString().c_str());
}
