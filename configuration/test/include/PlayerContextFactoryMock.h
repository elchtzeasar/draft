#ifndef PLAYER_CONTEXT_FACTORY_MOCK_H_
#define PLAYER_CONTEXT_FACTORY_MOCK_H_

#include "PlayerContextFactory.h"

#include <gmock/gmock.h>

class PlayerContextFactoryMock : public PlayerContextFactory {
 public:
  ~PlayerContextFactoryMock() {}

  MOCK_METHOD0(createPlayerContext, PlayerContext*());
};

#endif // PLAYER_CONTEXT_FACTORY_MOCK_H_
