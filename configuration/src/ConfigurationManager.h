#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <QtGlobal>

#include <string>

class PlayerContext;
class PlayerId;

class ConfigurationManager {
 public:
  virtual ~ConfigurationManager() {}

  virtual void setOwnPlayerId(const PlayerId& playerId) = 0;
  virtual void setPlayerContext(const PlayerId& playerId, const std::string& playerName) = 0;
  virtual const PlayerContext& getPlayerContext(const PlayerId& playerId) const = 0;
};

#endif // CONFIGURATION_MANAGER_H_
