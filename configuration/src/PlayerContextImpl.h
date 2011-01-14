#ifndef PLAYER_CONTEXT_IMPL_H_
#define PLAYER_CONTEXT_IMPL_H_

#include "PlayerContext.h"

class PlayerContextImpl : public PlayerContext {
 public:
  PlayerContextImpl();
  virtual ~PlayerContextImpl();

  virtual const std::string& getPlayerName() const;
  virtual void setPlayerName(const std::string& playerName);
 private:
  PlayerContextImpl(const PlayerContext&);
  PlayerContextImpl& operator=(PlayerContext&);

  std::string playerName;
};

#endif // PLAYER_CONTEXT_IMPL_H_
