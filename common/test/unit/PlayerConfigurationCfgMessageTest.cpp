#include "PlayerConfigurationCfgMessage.h"

#include <QByteArray>
#include <QDataStream>
#include <QString>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

using std::stringstream;
class PlayerConfigurationCfgMessageTest : public testing::Test {
protected:
  static const char* PLAYER_NAME;
};

const char* PlayerConfigurationCfgMessageTest::PLAYER_NAME("PLAYER NAME");

TEST_F(PlayerConfigurationCfgMessageTest, shouldPrintMessageCorrectly) {
  stringstream s;
  PlayerConfigurationCfgMessage playerNameCfgMessage(PLAYER_NAME);
  s << playerNameCfgMessage;

  ASSERT_EQ("PlayerConfigurationCfgMessage { playerName='PLAYER NAME' }", s.str());
}

TEST_F(PlayerConfigurationCfgMessageTest,
       shouldGetACopyOfPlayerConfigurationCfgMessageAfterSerializingThenDeserializing) {
  PlayerConfigurationCfgMessage playerNameCfgMessage1(PLAYER_NAME);
  PlayerConfigurationCfgMessage playerNameCfgMessage2;
  Message& message1(playerNameCfgMessage1);
  Message& message2(playerNameCfgMessage2);

  QByteArray byteArray;
  QDataStream writeStream(&byteArray, QIODevice::WriteOnly);
  QDataStream readStream(&byteArray, QIODevice::ReadOnly);

  writeStream.setVersion(QDataStream::Qt_4_0);
  readStream.setVersion(QDataStream::Qt_4_0);

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(playerNameCfgMessage1, playerNameCfgMessage2);
}
