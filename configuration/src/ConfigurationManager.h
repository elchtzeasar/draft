#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <QtGlobal>

#include <string>

class PlayerContext;

class ConfigurationManager {
 public:
  virtual ~ConfigurationManager() {}

  virtual void setOwnPlayerId(quint8 playerId) = 0;
  virtual void setPlayerContext(quint8 playerId, const std::string& playerName) = 0;
  virtual const PlayerContext& getPlayerContext(quint8 playerId) const = 0;
};

#endif // CONFIGURATION_MANAGER_H_
