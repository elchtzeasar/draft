#include "ConfigurationLoaderImpl.h"

#include "PlayerContextMock.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <sys/stat.h>

#include <gtest/gtest.h>

using testing::_;
using testing::Return;
using testing::ReturnRef;

using std::ofstream;

static const char* FILENAME("testFile.xml");
static const std::string PLAYER_NAME("playername");

class ConfigurationLoaderTest : public testing::Test {
protected:
  ConfigurationLoaderTest() : configurationLoader(FILENAME, playerContext) {
    removeXmlFile();
  }
  ~ConfigurationLoaderTest() {
    removeXmlFile();
  }

  PlayerContextMock playerContext;
  ConfigurationLoaderImpl configurationLoader;

  void writeToXmlFile(const std::string xmlData) {
    ofstream file;
    file.open(FILENAME);
    file << xmlData;
    file.close();
  }

  void removeXmlFile() {
    // Write to file so we dont get an error when we remove it if the test didn't:
    writeToXmlFile(FILENAME);
    remove(FILENAME);
  }
};

TEST_F(ConfigurationLoaderTest, shouldNotSetNameIfNoXmlFileFound) {
  EXPECT_CALL(playerContext, setPlayerName(_)).Times(0);

  configurationLoader.load();
}

TEST_F(ConfigurationLoaderTest, shouldNotSetNameIfNoneFoundInXmlFile) {
  writeToXmlFile("");
  EXPECT_CALL(playerContext, setPlayerName(_)).Times(0);

  configurationLoader.load();
}

TEST_F(ConfigurationLoaderTest, shouldSetNameIfFoundInXmlFile) {
  writeToXmlFile("<configuration><player><name>playername</name></player></configuration>");
  EXPECT_CALL(playerContext, setPlayerName(PLAYER_NAME));

  configurationLoader.load();
}

TEST_F(ConfigurationLoaderTest, shouldSaveConfigurationInXml) {
  writeToXmlFile("");
  PlayerContextMock playerContext2;
  ConfigurationLoaderImpl configurationLoader2(FILENAME, playerContext2);

  EXPECT_CALL(playerContext, getPlayerName()).WillOnce(ReturnRef(PLAYER_NAME));
  EXPECT_CALL(playerContext2, setPlayerName(PLAYER_NAME));

  configurationLoader.save();
  configurationLoader2.load();
}
