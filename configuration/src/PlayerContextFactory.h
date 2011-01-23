#ifndef PLAYER_CONTEXT_FACTORY_H_
#define PLAYER_CONTEXT_FACTORY_H_

class PlayerContext;

class PlayerContextFactory {
 public:
  virtual ~PlayerContextFactory() {}

  virtual PlayerContext* createPlayerContext() = 0;
};

#endif // PLAYER_CONTEXT_FACTORY_H_
