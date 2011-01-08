#include "ConfigurationComponent.h"

#include "ConfigurationManagerMock.h"
#include "ConfigurationLoaderMock.h"

#include <gtest/gtest.h>

#include <QList>
#include <QSignalSpy>
#include <QString>
#include <QVariant>

#include <iostream>

using testing::Return;
using testing::ReturnRef;
using testing::Throw;
using testing::_;

using std::string;
using std::ostream;

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest()
    :   configurationManager(new ConfigurationManagerMock),
	configurationLoader(new ConfigurationLoaderMock),
	configurationComponent(configurationManager, configurationLoader),
	responseSpy(&configurationComponent, SIGNAL(configurationResponse(const QString&))) {
  }

  ~ConfigurationComponentTest() {}

  ConfigurationManagerMock* configurationManager;
  ConfigurationLoaderMock* configurationLoader;
  ConfigurationComponent configurationComponent;
  QSignalSpy responseSpy;

  static const std::string PLAYER_NAME;
};

ostream& operator<<(ostream& os, const QString& qString);

const std::string ConfigurationComponentTest::PLAYER_NAME = "Player Name";

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithConfigurationResponseWithCorrectPlayerName) {
  EXPECT_CALL(*configurationManager, getPlayerName()).WillOnce(ReturnRef(PLAYER_NAME));

  configurationComponent.configurationRequest();

  ASSERT_EQ(1, responseSpy.count());
  QList<QVariant> arguments = responseSpy.takeFirst();
  ASSERT_EQ(PLAYER_NAME, arguments.at(0).toString().toStdString());
}

TEST_F(ConfigurationComponentTest, shouldSetPlayerNameInManagerOnSetPlayerName) {
  QString playerName("player name");
  EXPECT_CALL(*configurationManager, setPlayerName(testing::StrEq(playerName.toStdString())));

  configurationComponent.setPlayerName(playerName);
}

TEST_F(ConfigurationComponentTest, shouldDeallocateSaveConfigurationUponExit) {
  EXPECT_CALL(*configurationLoader, save()).WillOnce(Return());

  configurationComponent.handleExit(0);
}

ostream& operator<<(ostream& os, const QString& qString) {
  os << qString.toStdString();
  return os;
}
