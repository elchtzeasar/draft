#include "ConfigurationManager.h"

#include <iostream>
#include <fstream>
#include <cstdio>

#include <gtest/gtest.h>

using std::ofstream;

static const char* FILENAME("testFile.xml");

class ConfigurationManagerTest : public testing::Test {
protected:
  ConfigurationManagerTest() : configurationManager(FILENAME) {}
  ~ConfigurationManagerTest() {
    remove(FILENAME);
  }

  ConfigurationManager configurationManager;

  void writeToFile(const std::string xmlData) {
    ofstream file;
    file.open(FILENAME);
    file << xmlData;
    file.close();
  }
};

TEST_F(ConfigurationManagerTest, shouldUseDefaultNameIfNoXmlFileFound) {
  configurationManager.load();

  ASSERT_EQ("Unknown player", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldUseDefaultNameIfNoneFoundInXmlFile) {
  writeToFile("");

  configurationManager.load();

  ASSERT_EQ("Unknown player", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldParseFileNameFromXml) {
  writeToFile("<configuration><player><name>playername</name></player></configuration>");

  configurationManager.load();

  ASSERT_EQ("playername", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldSaveConfigurationInXml) {
  writeToFile("");

  configurationManager.setPlayerName("playername");
  configurationManager.save();
  ConfigurationManager configurationManager2(FILENAME);
  configurationManager2.load();

  ASSERT_EQ("playername", configurationManager2.getPlayerName());
}
