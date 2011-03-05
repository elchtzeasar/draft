#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <QtGlobal>

#include <QString>

class PlayerContext;
class PlayerId;

class ConfigurationManager {
 public:
  virtual ~ConfigurationManager() {}

  virtual void setOwnPlayerId(const PlayerId& playerId) = 0;
  virtual void setPlayerContext(const PlayerId& playerId, const QString& playerName) = 0;
  virtual const PlayerContext& getPlayerContext(const PlayerId& playerId) const = 0;
};

#endif // CONFIGURATION_MANAGER_H_
