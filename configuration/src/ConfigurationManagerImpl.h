#ifndef CONFIGURATION_MANAGER_IMPL_H_
#define CONFIGURATION_MANAGER_IMPL_H_

#include "ConfigurationManager.h"

#include <map>

class PlayerContext;
class PlayerContextFactory;

typedef std::map<PlayerId, PlayerContext*> PlayerContextMap;

class ConfigurationManagerImpl : public ConfigurationManager {
 public:
  ConfigurationManagerImpl(PlayerContext* ownPlayerContext,
			   PlayerContextFactory* playerContextFactory);
  virtual ~ConfigurationManagerImpl();

  void setOwnPlayerId(const PlayerId& playerId);
  void setPlayerContext(const PlayerId& playerId, const QString& playerName);
  const PlayerContext& getPlayerContext(const PlayerId& playerId) const;

 private:
  ConfigurationManagerImpl(const ConfigurationManagerImpl&);
  ConfigurationManagerImpl& operator=(ConfigurationManagerImpl&);

  PlayerContextFactory* playerContextFactory;

  PlayerContextMap playerContexts;
};

#endif // CONFIGURATION_MANAGER_IMPL_H_
