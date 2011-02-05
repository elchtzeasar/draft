#include "ConfigurationManagerImpl.h"

#include "PlayerContextFactoryMock.h"
#include "PlayerContextMock.h"
#include "PlayerId.h"

#include <gtest/gtest.h>

#include <string>

using testing::Return;
using testing::NiceMock;

const quint8 PLAYER_ID(21);
const std::string PLAYER_NAME("Name of player");

class ConfigurationManagerTest : public testing::Test {
protected:
  ConfigurationManagerTest() : ownPlayerContext(new NiceMock<PlayerContextMock>),
			       newPlayerContext(new NiceMock<PlayerContextMock>),
			       playerContextFactory(new NiceMock<PlayerContextFactoryMock>),
			       configurationManager(ownPlayerContext, playerContextFactory) {}

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

