#ifndef CONFIGURATION_MANAGER_MOCK_H_
#define CONFIGURATION_MANAGER_MOCK_H_

#include "ConfigurationManager.h"

#include <gmock/gmock.h>

class ConfigurationManagerMock : public ConfigurationManager {
 public:
  ConfigurationManagerMock() {}
  virtual ~ConfigurationManagerMock() {}

  MOCK_METHOD1(setOwnPlayerId, void(const PlayerId& playerId));
  MOCK_METHOD2(setPlayerContext, void(const PlayerId& playerId, const std::string& playerName));
  MOCK_CONST_METHOD1(getPlayerContext, const PlayerContext&(const PlayerId& playerId));
};

#endif // CONFIGURATION_MANAGER_MOCK_H_
