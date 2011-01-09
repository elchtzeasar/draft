#include "ConfigurationComponent.h"

#include "ConfigurationManagerMock.h"
#include "ConfigurationLoaderMock.h"

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

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest()
    :   configurationManager(new NiceMock<ConfigurationManagerMock>),
	configurationLoader(new ConfigurationLoaderMock),
	configurationComponent(configurationManager, configurationLoader),
	responseSpy(&configurationComponent, SIGNAL(configurationResponse(quint8, const QString&))) {
  }

  ~ConfigurationComponentTest() {}

  NiceMock<ConfigurationManagerMock>* configurationManager;
  ConfigurationLoaderMock* configurationLoader;
  ConfigurationComponent configurationComponent;
  QSignalSpy responseSpy;
};

static const std::string PLAYER_NAME = "Player Name";
static const quint8 PLAYER_ID(15);

ostream& operator<<(ostream& os, const QString& qString);

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithConfigurationResponseWithCorrectPlayerName) {
  EXPECT_CALL(*configurationManager, getPlayerName()).WillOnce(ReturnRef(PLAYER_NAME));

  configurationComponent.configurationRequest(PLAYER_ID);

  ASSERT_EQ(1, responseSpy.count());
  QList<QVariant> arguments = responseSpy.takeFirst();
  ASSERT_EQ(PLAYER_NAME, arguments.at(1).toString().toStdString());
}

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithConfigurationResponseWithCorrectPlayerId) {
  ON_CALL(*configurationManager, getPlayerName()).WillByDefault(ReturnRef(PLAYER_NAME));

  configurationComponent.configurationRequest(PLAYER_ID);

  ASSERT_EQ(1, responseSpy.count());
  QList<QVariant> arguments = responseSpy.takeFirst();
  ASSERT_EQ(PLAYER_ID, arguments.at(0).toUInt());
}

TEST_F(ConfigurationComponentTest, shouldSetPlayerNameInManagerOnSetPlayerName) {
  QString playerName("player name");
  EXPECT_CALL(*configurationManager, setPlayerName(testing::StrEq(playerName.toStdString())));

  configurationComponent.setPlayerName(PLAYER_ID, playerName);
}

TEST_F(ConfigurationComponentTest, shouldDeallocateSaveConfigurationUponExit) {
  EXPECT_CALL(*configurationLoader, save()).WillOnce(Return());

  configurationComponent.handleExit(0);
}

ostream& operator<<(ostream& os, const QString& qString) {
  os << qString.toStdString();
  return os;
}
