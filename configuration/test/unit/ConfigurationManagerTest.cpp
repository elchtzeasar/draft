#include "ConfigurationManagerImpl.h"

#include "PlayerContextFactoryMock.h"
#include "PlayerContextMock.h"
#include "PlayerId.h"

#include <gtest/gtest.h>
#include "mock-log.h"

#include <QString>

using google::glog_testing::ScopedMockLog;
using testing::_;
using testing::Return;
using testing::NiceMock;

const quint8 PLAYER_ID(21);
const QString PLAYER_NAME("Name of player");

class ConfigurationManagerTest : public testing::Test {
protected:
  ConfigurationManagerTest() : ownPlayerContext(new NiceMock<PlayerContextMock>),
			       newPlayerContext(new NiceMock<PlayerContextMock>),
			       playerContextFactory(new NiceMock<PlayerContextFactoryMock>),
			       configurationManager(ownPlayerContext, playerContextFactory) {
  }

  NiceMock<PlayerContextMock>* ownPlayerContext;
  NiceMock<PlayerContextMock>* newPlayerContext;
  NiceMock<PlayerContextFactoryMock>* playerContextFactory;
  ConfigurationManagerImpl configurationManager;
};

TEST_F(ConfigurationManagerTest, shouldReturnOwnPlayerContextAfterSettingOwnPlayerIdAndUsingItToFetchAPlayerContext) {
  configurationManager.setOwnPlayerId(PLAYER_ID);

  ASSERT_EQ(*ownPlayerContext,
	    configurationManager.getPlayerContext(PLAYER_ID));
}

TEST_F(ConfigurationManagerTest, shouldCreatePlayerContextOnCreatePlayerContextIfNoPlayerExists) {
  EXPECT_CALL(*playerContextFactory, createPlayerContext()).WillOnce(Return(newPlayerContext));

  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldLogErrorOnCreatePlayerContextIfPlayerExists) {
  ScopedMockLog log;
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  EXPECT_CALL(log, Log(ERROR, _, "createPlayerContext called with PlayerId=21, "
                       "There is allready a context with that id, not doing anything."));

  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);
  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldNotCreatePlayerContextOnCreatePlayerContextIfPlayerExists) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));
  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);

  EXPECT_CALL(*playerContextFactory, createPlayerContext()).Times(0);

  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldSetCorrectParametersOnCreatePlayerContext) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  EXPECT_CALL(*newPlayerContext, setPlayerName(PLAYER_NAME));

  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldLogErrorOnUpdatePlayerContextWhenNoContextExists) {
  ScopedMockLog log;
  EXPECT_CALL(log, Log(ERROR, _, "updatePlayerContext called with PlayerId=21, "
                       "there is no context for that id, not doing anything."));

  configurationManager.updatePlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldSetCorrectParametersOnUpdatePlayerContext) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));
  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);

  EXPECT_CALL(*newPlayerContext, setPlayerName(PLAYER_NAME));

  configurationManager.updatePlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldReturnOwnPlayerContextWhenPlayerIdIsOwnPlayerId) {
  ASSERT_EQ(*ownPlayerContext,
	    configurationManager.getPlayerContext(PlayerId::OWN));
}

TEST_F(ConfigurationManagerTest, shouldReturnCorrectPlayerContextWhenFetchingWithPlayerId) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  configurationManager.createPlayerContext(PLAYER_ID, PLAYER_NAME);

  ASSERT_EQ(*newPlayerContext, configurationManager.getPlayerContext(PLAYER_ID));
}

