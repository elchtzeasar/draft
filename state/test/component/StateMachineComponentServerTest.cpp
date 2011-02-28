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

class StateMachineComponentServerTest : public testing::Test {
 public:
  StateMachineComponentServerTest();

 protected:
  const PlayerId playerId;
  QCoreApplication* application;
  RemoteControllerStub remoteController;
  ConfigurationComponentStub configurationComponent;
  NetworkComponentStub networkComponent;
  StateMachineComponent stateMachineComponent;
  DraftApplication draftApplication;

  StateChangeWaiter stateChangeWaiter;

  void startComponentAndWait();
  void hostDraftAndWait();
  void sendClientConnectedAndWait();
  void confirmPlayerIdAndWait();
  void sendPlayerNameAndWait();
};

StateMachineComponentServerTest::StateMachineComponentServerTest() :
  playerId(5),
  application(QCoreApplication::instance()),
  draftApplication(*application, remoteController, configurationComponent,
		   networkComponent, stateMachineComponent),
  stateChangeWaiter(stateMachineComponent) {
    qRegisterMetaType<AddressedMessage>("AddressedMessage");
    qRegisterMetaType<PlayerId>("PlayerId");

    draftApplication.connectSlotsToSignals();
}

void StateMachineComponentServerTest::startComponentAndWait() {
  stateMachineComponent.start();

  ASSERT_TRUE(stateChangeWaiter.wait("ChooseClientOrServer"));
}

void StateMachineComponentServerTest::hostDraftAndWait() {
  remoteController.sendHostDraft(DONT_CARE);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ListeningForConnections"));
}

void StateMachineComponentServerTest::sendClientConnectedAndWait() {
  networkComponent.sendClientConnected(playerId);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ListeningForConnections"));
}

void StateMachineComponentServerTest::confirmPlayerIdAndWait() {
  const AddressedMessage playerIdCnf(new AddressHeader(playerId, PlayerId::SERVER),
                                     new NullMessage(MessageNumber::PLAYER_ID_CNF));
  networkComponent.sendDataReceived(playerIdCnf);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ClientStateMachine::Configuring::ReceivingClientName"));
}

void StateMachineComponentServerTest::sendPlayerNameAndWait() {
  const AddressedMessage playerNameCfg(new AddressHeader(playerId, PlayerId::SERVER),
				       new PlayerNameCfgMessage("Other player"));

  networkComponent.sendDataReceived(playerNameCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ClientStateMachine::Configuring::SavingPlayerName"));
}

TEST_F(StateMachineComponentServerTest, shouldSendPlayerIdCfgWhenClientConnected) {
  AddressedMessage expectedPlayerIdCfg(new AddressHeader(PlayerId::SERVER, playerId),
				       new NullMessage(MessageNumber::PLAYER_ID_CFG));

  startComponentAndWait();
  hostDraftAndWait();
  sendClientConnectedAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerIdCfg));
}

TEST_F(StateMachineComponentServerTest, shouldSendPlayerNameCnfWhenPlayerNameCfgReceived) {
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(PlayerId::SERVER, playerId),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  hostDraftAndWait();
  sendClientConnectedAndWait();
  confirmPlayerIdAndWait();
  sendPlayerNameAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCnf));
}
