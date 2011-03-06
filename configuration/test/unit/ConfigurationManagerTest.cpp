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

TEST_F(ConfigurationManagerTest, shouldCreatePlayerContextOnSetPlayerContextIfNoPlayerExists) {
  EXPECT_CALL(*playerContextFactory, createPlayerContext()).WillOnce(Return(newPlayerContext));

  configurationManager.setPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldLogWarningOnSetPlayerContextIfNoPlayerExists) {
  ScopedMockLog log;
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  EXPECT_CALL(log, Log(WARNING, _, "setPlayerContext called for PlayerId=21, it should "
                       "be created first with createPlayerContext. Creating context anyways."));

  configurationManager.setPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldNotCreatePlayerContextOnSetPlayerContextIfPlayerAllreadyExists) {
  EXPECT_CALL(*playerContextFactory, createPlayerContext()).Times(0);

  configurationManager.setPlayerContext(PlayerId::OWN, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldSetCorrectParametersInNewPlayerContextOnSetPlayerContext) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  EXPECT_CALL(*newPlayerContext, setPlayerName(PLAYER_NAME));

  configurationManager.setPlayerContext(PLAYER_ID, PLAYER_NAME);
}

TEST_F(ConfigurationManagerTest, shouldReturnOwnPlayerContextWhenPlayerIdIsOwnPlayerId) {
  ASSERT_EQ(*ownPlayerContext,
	    configurationManager.getPlayerContext(PlayerId::OWN));
}

TEST_F(ConfigurationManagerTest, shouldReturnCorrectPlayerContextWhenFetchingWithPlayerId) {
  ON_CALL(*playerContextFactory, createPlayerContext()).WillByDefault(Return(newPlayerContext));

  configurationManager.setPlayerContext(PLAYER_ID, PLAYER_NAME);

  ASSERT_EQ(*newPlayerContext, configurationManager.getPlayerContext(PLAYER_ID));
}

