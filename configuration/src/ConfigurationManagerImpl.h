#ifndef CONFIGURATION_MANAGER_IMPL_H_
#define CONFIGURATION_MANAGER_IMPL_H_

#include "ConfigurationManager.h"

#include <map>

class PlayerContext;
class PlayerContextFactory;

typedef std::map<quint8, PlayerContext*> PlayerContextMap;

class ConfigurationManagerImpl : public ConfigurationManager {
 public:
  ConfigurationManagerImpl(PlayerContext* ownPlayerContext,
			   PlayerContextFactory* playerContextFactory);
  virtual ~ConfigurationManagerImpl();

  void setOwnPlayerId(quint8 playerId);
  void setPlayerContext(quint8 playerId, const std::string& playerName);
  const PlayerContext& getPlayerContext(quint8 playerId) const;

 private:
  ConfigurationManagerImpl(const ConfigurationManagerImpl&);
  ConfigurationManagerImpl& operator=(ConfigurationManagerImpl&);

  PlayerContextFactory* playerContextFactory;

  PlayerContextMap playerContexts;
};

#endif // CONFIGURATION_MANAGER_IMPL_H_
