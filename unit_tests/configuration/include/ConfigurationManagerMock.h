#include "ConfigurationManager.h"

#include <gmock/gmock.h>

class ConfigurationManagerMock : public ConfigurationManager {
 public:
  ConfigurationManagerMock() {}
  virtual ~ConfigurationManagerMock() {}

  MOCK_METHOD0(load, void());
  MOCK_CONST_METHOD0(save, void());
  MOCK_CONST_METHOD0(getPlayerName, const std::string&());
  MOCK_METHOD1(setPlayerName, void(const std::string& playerName));
};
