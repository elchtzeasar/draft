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

class StateMachineComponentServerTest : public testing::Test {
 public:
  StateMachineComponentServerTest();

 protected:
  static const PlayerId PLAYER_ID;
  static const char* PLAYER_NAME;

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

const PlayerId StateMachineComponentServerTest::PLAYER_ID(5);
const char* StateMachineComponentServerTest::PLAYER_NAME("Other player");

StateMachineComponentServerTest::StateMachineComponentServerTest() :
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
  networkComponent.sendClientConnected(PLAYER_ID);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ListeningForConnections"));
}

void StateMachineComponentServerTest::confirmPlayerIdAndWait() {
  const AddressedMessage playerIdCnf(new AddressHeader(PLAYER_ID, PlayerId::SERVER),
                                     new NullMessage(MessageNumber::PLAYER_ID_CNF));
  networkComponent.sendDataReceived(playerIdCnf);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ClientStateMachine::Configuring::ReceivingClientName"));
}

void StateMachineComponentServerTest::sendPlayerNameAndWait() {
  const AddressedMessage playerNameCfg(new AddressHeader(PLAYER_ID, PlayerId::SERVER),
				       new PlayerNameCfgMessage(PLAYER_NAME));

  networkComponent.sendDataReceived(playerNameCfg);

  ASSERT_TRUE(stateChangeWaiter.wait("Server::ClientStateMachine::Configuring::SavingPlayerName"));
}

TEST_F(StateMachineComponentServerTest, shouldSendPlayerIdCfgWhenClientConnected) {
  AddressedMessage expectedPlayerIdCfg(new AddressHeader(PlayerId::SERVER, PLAYER_ID),
				       new NullMessage(MessageNumber::PLAYER_ID_CFG));

  startComponentAndWait();
  hostDraftAndWait();
  sendClientConnectedAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerIdCfg));
}

TEST_F(StateMachineComponentServerTest, shouldSendPlayerNameCnfWhenPlayerNameCfgReceived) {
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(PlayerId::SERVER, PLAYER_ID),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  hostDraftAndWait();
  sendClientConnectedAndWait();
  confirmPlayerIdAndWait();
  sendPlayerNameAndWait();

  ASSERT_TRUE(networkComponent.waitForSendData(expectedPlayerNameCnf));
}

TEST_F(StateMachineComponentServerTest, shouldEmitPlayerConnectedWhenPlayerNameCfgReceived) {
  QSignalSpy playerConnectedSpy(&stateMachineComponent,
                                SIGNAL(playerConnected(const PlayerId&, const QString&)));
  AddressedMessage expectedPlayerNameCnf(new AddressHeader(PlayerId::SERVER, PLAYER_ID),
                                         new NullMessage(MessageNumber::PLAYER_NAME_CNF));

  startComponentAndWait();
  hostDraftAndWait();
  sendClientConnectedAndWait();
  confirmPlayerIdAndWait();
  sendPlayerNameAndWait();

  ASSERT_EQ(1, playerConnectedSpy.count());
  QList<QVariant> arguments = playerConnectedSpy.takeFirst();
  ASSERT_EQ(PLAYER_ID, arguments.at(0).value<PlayerId>());
  ASSERT_STREQ(PLAYER_NAME, arguments.at(1).toString().toStdString().c_str());
}
