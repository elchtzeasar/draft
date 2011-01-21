#ifndef CONFIGURATION_MANAGER_IMPL_H_
#define CONFIGURATION_MANAGER_IMPL_H_

#include "ConfigurationManager.h"

class ConfigurationManagerImpl : public ConfigurationManager {
 public:
  virtual ~ConfigurationManagerImpl();

  void setOwnPlayerId(quint8 playerId);
  void setPlayerContext(quint8 playerId, const std::string& playerName);
  const PlayerContext& getPlayerContext(quint8 playerId) const;
};

#endif // CONFIGURATION_MANAGER_IMPL_H_
