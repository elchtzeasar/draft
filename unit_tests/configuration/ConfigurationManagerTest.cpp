#include "ConfigurationManagerImpl.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <sys/stat.h>

#include <gtest/gtest.h>

using std::ofstream;

static const char* FILENAME("testFile.xml");

class ConfigurationManagerTest : public testing::Test {
protected:
  ConfigurationManagerTest() : configurationManager(FILENAME) {
    removeXmlFile();
  }
  ~ConfigurationManagerTest() {
    removeXmlFile();
  }

  ConfigurationManagerImpl configurationManager;

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

TEST_F(ConfigurationManagerTest, shouldUseDefaultNameIfNoXmlFileFound) {
  configurationManager.load();

  ASSERT_EQ("Unknown player", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldUseDefaultNameIfNoneFoundInXmlFile) {
  writeToXmlFile("");

  configurationManager.load();

  ASSERT_EQ("Unknown player", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldParseFileNameFromXml) {
  writeToXmlFile("<configuration><player><name>playername</name></player></configuration>");

  configurationManager.load();

  ASSERT_EQ("playername", configurationManager.getPlayerName());
}

TEST_F(ConfigurationManagerTest, shouldSaveConfigurationInXml) {
  writeToXmlFile("");

  configurationManager.setPlayerName("playername");
  configurationManager.save();
  ConfigurationManagerImpl configurationManager2(FILENAME);
  configurationManager2.load();

  ASSERT_EQ("playername", configurationManager2.getPlayerName());
}
