#ifndef PLAYER_CONTEXT_H_
#define PLAYER_CONTEXT_H_

#include <string>

class PlayerContext {
 public:
  virtual ~PlayerContext() {}

  virtual const std::string& getPlayerName() const = 0;
  virtual void setPlayerName(const std::string& playerName) = 0;
};

#endif // PLAYER_CONTEXT_H_
