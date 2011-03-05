#ifndef PLAYER_CONTEXT_H_
#define PLAYER_CONTEXT_H_

class QString;

class PlayerContext {
 public:
  virtual ~PlayerContext() {}

  virtual const QString& getPlayerName() const = 0;
  virtual void setPlayerName(const QString& playerName) = 0;
};

#endif // PLAYER_CONTEXT_H_
