#include "ConfigurationComponentFactory.h"
#include "ConfigurationComponent.h"
#include "PlayerId.h"
#include "QStringStreams.h"
#include "SignalWaiter.h"

#include <gtest/gtest.h>

#include <QList>
#include <QSignalSpy>
#include <QString>
#include <QVariant>

class ConfigurationComponentTest : public testing::Test {
protected:
  ConfigurationComponentTest();

  PlayerId extractPlayerIdFromConfigurationResponse() const;
  QString extractPlayerNameFromConfigurationResponse() const;
  
  static const PlayerId PLAYER_ID;
  static const QString PLAYER_NAME;
  static const QString OWN_PLAYER_NAME;

  ConfigurationComponentFactory configurationComponentFactory;
  ConfigurationComponent* configurationComponent;

  QSignalSpy configurationResponseSpy;
  SignalWaiter configurationResponseWaiter;
};

ConfigurationComponentTest::ConfigurationComponentTest() :
  configurationComponentFactory(),
  configurationComponent(configurationComponentFactory.createComponent()),
  configurationResponseSpy(configurationComponent,
                           SIGNAL(configurationResponse(const PlayerId&,
                                                        const QString&))),
  configurationResponseWaiter(configurationResponseSpy) {
}

TEST_F(ConfigurationComponentTest, shouldUpdateOwnPlayerIdWhenSetOwnPlayerIdCalled) {
  configurationComponent->handleSetPlayerName(PlayerId::OWN, OWN_PLAYER_NAME);
  configurationComponent->handleSetOwnPlayerId(PLAYER_ID);

  configurationComponent->handleConfigurationRequest(PLAYER_ID);
  configurationResponseWaiter.wait();

  ASSERT_EQ(1, configurationResponseSpy.count());
  ASSERT_EQ(PLAYER_ID, extractPlayerIdFromConfigurationResponse());
  ASSERT_EQ(OWN_PLAYER_NAME, extractPlayerNameFromConfigurationResponse());
}

TEST_F(ConfigurationComponentTest, shouldRespondToConfigurationRequestWithConfigurationResponseForCorrectPlayer) {
  configurationComponent->handleSetPlayerName(PLAYER_ID, PLAYER_NAME);

  configurationComponent->handleConfigurationRequest(PLAYER_ID);
  configurationResponseWaiter.wait();

  ASSERT_EQ(1, configurationResponseSpy.count());
  ASSERT_EQ(PLAYER_ID, extractPlayerIdFromConfigurationResponse());
  ASSERT_EQ(PLAYER_NAME, extractPlayerNameFromConfigurationResponse());
}

PlayerId ConfigurationComponentTest::extractPlayerIdFromConfigurationResponse() const {
  QList<QVariant> arguments = configurationResponseSpy.first();
  return arguments.at(0).value<PlayerId>();
}

QString ConfigurationComponentTest::extractPlayerNameFromConfigurationResponse() const {
  QList<QVariant> arguments = configurationResponseSpy.first();
  return arguments.at(1).toString();
}

const PlayerId ConfigurationComponentTest::PLAYER_ID(101);
const QString ConfigurationComponentTest::PLAYER_NAME("[player name]");
const QString ConfigurationComponentTest::OWN_PLAYER_NAME("[own player name]");
