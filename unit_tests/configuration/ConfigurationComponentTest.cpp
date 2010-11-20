#include "ConfigurationComponent.h"
#include "ConfigurationManagerMock.h"

#include <gtest/gtest.h>

#include <QSignalSpy>
#include <QList>
#include <QVariant>

#include <iostream>

using testing::ReturnRef;
using testing::Throw;
using testing::_;

using std::string;
using std::ostream;

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest()
    :   configurationManager(new ConfigurationManagerMock),
	configurationComponent(configurationManager),
	responseSpy(&configurationComponent, SIGNAL(configurationResponse(const QString&))) {
    ON_CALL(*configurationManager, save()).WillByDefault(Throw("Mock the call!"));
    ON_CALL(*configurationManager, load()).WillByDefault(Throw("Mock the call!"));
    ON_CALL(*configurationManager, getPlayerName()).WillByDefault(Throw("Mock the call!"));
    ON_CALL(*configurationManager, setPlayerName(_)).WillByDefault(Throw("Mock the call!"));
  }

  ~ConfigurationComponentTest() {
  }

  ConfigurationManagerMock* configurationManager;
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

ostream& operator<<(ostream& os, const QString& qString) {
  os << qString.toStdString();
  return os;
}
