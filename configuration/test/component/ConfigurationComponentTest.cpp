#include "ConfigurationComponent.h"

#include "PlayerContextMock.h"
#include "PlayerId.h"
#include "ConfigurationLoaderMock.h"
#include "ConfigurationManagerMock.h"

#include <gtest/gtest.h>

#include <QList>
#include <QSignalSpy>
#include <QString>
#include <QVariant>

using testing::NiceMock;
using testing::Return;
using testing::ReturnRef;
using testing::Throw;
using testing::_;

using std::string;
using std::ostream;

static const QString PLAYER_NAME = "Player Name";
static const PlayerId PLAYER_ID(15);

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest()
    :   configurationManager(new NiceMock<ConfigurationManagerMock>),
	configurationLoader(new ConfigurationLoaderMock),
	configurationComponent(configurationManager, configurationLoader),
	responseSpy(&configurationComponent, SIGNAL(configurationResponse(const PlayerId&, const QString&))) {
    ON_CALL(*configurationManager, getPlayerContext(PLAYER_ID)).
      WillByDefault(ReturnRef(playerContext));
    ON_CALL(playerContext, getPlayerName()).WillByDefault(ReturnRef(PLAYER_NAME));

    qRegisterMetaType<PlayerId>("PlayerId");
  }

  ~ConfigurationComponentTest() {}

  NiceMock<PlayerContextMock> playerContext;
  NiceMock<ConfigurationManagerMock>* configurationManager;
  ConfigurationLoaderMock* configurationLoader;
  ConfigurationComponent configurationComponent;
  QSignalSpy responseSpy;
};

TEST_F(ConfigurationComponentTest, shouldRequestPlayerContextFromPlayerManagerWhenConfigurationRequestReceived) {
  EXPECT_CALL(*configurationManager, getPlayerContext(PLAYER_ID)).
    WillOnce(ReturnRef(playerContext));

  configurationComponent.handleConfigurationRequest(PLAYER_ID);
}

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithCorrectConfigurationResponse) {
  configurationComponent.handleConfigurationRequest(PLAYER_ID);

  ASSERT_EQ(1, responseSpy.count());
  QList<QVariant> arguments = responseSpy.takeFirst();
  ASSERT_EQ(PLAYER_NAME, arguments.at(1).toString());
  ASSERT_EQ(PLAYER_ID, arguments.at(0).value<PlayerId>());
}

TEST_F(ConfigurationComponentTest, shouldUpdateOwnPlayerIdInManagerUponSetOwnPlayerId) {
  EXPECT_CALL(*configurationManager, setOwnPlayerId(PLAYER_ID));

  configurationComponent.handleSetOwnPlayerId(PLAYER_ID);
}

TEST_F(ConfigurationComponentTest, shouldSetPlayerContextInManagerOnSetPlayerName) {
  QString playerName("player name");
  EXPECT_CALL(*configurationManager, setPlayerContext(PLAYER_ID, playerName));

  configurationComponent.handleSetPlayerName(PLAYER_ID, playerName);
}

TEST_F(ConfigurationComponentTest, shouldSaveConfigurationUponExit) {
  EXPECT_CALL(*configurationLoader, save()).WillOnce(Return());

  configurationComponent.handleExit(0);
}
