#ifndef PLAYER_CONTEXT_FACTORY_IMPL_H_
#define PLAYER_CONTEXT_FACTORY_IMPL_H_

#include "PlayerContextFactory.h"

class PlayerContextFactoryImpl : public PlayerContextFactory {
 public:
  virtual ~PlayerContextFactoryImpl();

  PlayerContext* createPlayerContext();
};

#endif // PLAYER_CONTEXT_FACTORY_IMPL_H_
