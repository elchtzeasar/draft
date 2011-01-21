#include "ConfigurationComponent.h"

#include "PlayerContextMock.h"
#include "ConfigurationLoaderMock.h"
#include "ConfigurationManagerMock.h"

#include <gtest/gtest.h>

#include <QList>
#include <QSignalSpy>
#include <QString>
#include <QVariant>

#include <iostream>

using testing::NiceMock;
using testing::Return;
using testing::ReturnRef;
using testing::Throw;
using testing::_;

using std::string;
using std::ostream;

ostream& operator<<(ostream& os, const QString& qString);

static const std::string PLAYER_NAME = "Player Name";
static const quint8 PLAYER_ID(15);

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest()
    :   configurationManager(new NiceMock<ConfigurationManagerMock>),
	configurationLoader(new ConfigurationLoaderMock),
	configurationComponent(configurationManager, configurationLoader),
	responseSpy(&configurationComponent, SIGNAL(configurationResponse(quint8, const QString&))) {
    ON_CALL(*configurationManager, getPlayerContext(PLAYER_ID)).
      WillByDefault(ReturnRef(playerContext));
    ON_CALL(playerContext, getPlayerName()).WillByDefault(ReturnRef(PLAYER_NAME));
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

  configurationComponent.configurationRequest(PLAYER_ID);
}

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithCorrectConfigurationResponse) {
  configurationComponent.configurationRequest(PLAYER_ID);

  ASSERT_EQ(1, responseSpy.count());
  QList<QVariant> arguments = responseSpy.takeFirst();
  ASSERT_EQ(PLAYER_NAME, arguments.at(1).toString().toStdString());
  ASSERT_EQ(PLAYER_ID, arguments.at(0).toUInt());
}

TEST_F(ConfigurationComponentTest, shouldUpdateOwnPlayerIdInManagerUponSetOwnPlayerId) {
  EXPECT_CALL(*configurationManager, setOwnPlayerId(PLAYER_ID));

  configurationComponent.setOwnPlayerId(PLAYER_ID);
}

TEST_F(ConfigurationComponentTest, shouldSetPlayerContextInManagerOnSetPlayerName) {
  QString playerName("player name");
  EXPECT_CALL(*configurationManager, setPlayerContext(PLAYER_ID, testing::StrEq(playerName.toStdString())));

  configurationComponent.setPlayerName(PLAYER_ID, playerName);
}

TEST_F(ConfigurationComponentTest, shouldSaveConfigurationUponExit) {
  EXPECT_CALL(*configurationLoader, save()).WillOnce(Return());

  configurationComponent.handleExit(0);
}

ostream& operator<<(ostream& os, const QString& qString) {
  os << qString.toStdString();
  return os;
}
