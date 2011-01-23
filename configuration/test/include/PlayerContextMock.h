#ifndef PLAYER_CONTEXT_MOCK
#define PLAYER_CONTEXT_MOCK

#include "PlayerContext.h"

#include <gmock/gmock.h>

#include <iostream>

class PlayerContextMock : public PlayerContext {
 public:
  PlayerContextMock() {}
  virtual ~PlayerContextMock() {}

  MOCK_METHOD0(load, void());
  MOCK_CONST_METHOD0(save, void());
  MOCK_CONST_METHOD0(getPlayerName, const std::string&());
  MOCK_METHOD1(setPlayerName, void(const std::string& playerName));
};

bool operator==(const PlayerContext& lhs, const PlayerContext& rhs);
std::ostream& operator<<(std::ostream& stream, const PlayerContext& playerContext);

#endif // PLAYER_CONTEXT_MOCK
