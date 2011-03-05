#ifndef PLAYER_CONTEXT_IMPL_H_
#define PLAYER_CONTEXT_IMPL_H_

#include "PlayerContext.h"
#include <QString>

class PlayerContextImpl : public PlayerContext {
 public:
  PlayerContextImpl();
  virtual ~PlayerContextImpl();

  virtual const QString& getPlayerName() const;
  virtual void setPlayerName(const QString& playerName);
 private:
  PlayerContextImpl(const PlayerContext&);
  PlayerContextImpl& operator=(PlayerContext&);

  QString playerName;
};

#endif // PLAYER_CONTEXT_IMPL_H_
