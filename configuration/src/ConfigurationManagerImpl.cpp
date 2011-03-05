#include "ConfigurationManagerImpl.h"

#include "PlayerContext.h"
#include "PlayerContextFactory.h"
#include "PlayerId.h"

#include <cassert>

using std::map;

ConfigurationManagerImpl::ConfigurationManagerImpl(PlayerContext* ownPlayerContext, PlayerContextFactory* playerContextFactory) :
  playerContextFactory(playerContextFactory) {
  playerContexts[PlayerId::OWN] = ownPlayerContext;
}

ConfigurationManagerImpl::~ConfigurationManagerImpl() {
  for (PlayerContextMap::iterator it(playerContexts.begin());
       it != playerContexts.end();
       ++it) {
    // TODO: The following assumes that the own player id is set, otherwise the own
    //       player context will not be deleted:
    if (it->first != PlayerId::OWN) {
      delete it->second;
    }
    it->second = NULL;
  }

  delete playerContextFactory;
}

void ConfigurationManagerImpl::setOwnPlayerId(const PlayerId& playerId) {
  PlayerContext* ownPlayerContext = playerContexts[PlayerId::OWN];
  playerContexts[playerId] = ownPlayerContext;
}

void ConfigurationManagerImpl::setPlayerContext(const PlayerId& playerId, const QString& playerName) {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));
  PlayerContext* playerContext(NULL);
  if (it == playerContexts.end())
    playerContext = playerContextFactory->createPlayerContext();
  else
    playerContext = it->second;

  playerContext->setPlayerName(playerName);
  playerContexts[playerId] = playerContext;
}

const PlayerContext& ConfigurationManagerImpl::getPlayerContext(const PlayerId& playerId) const {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));

  assert(it != playerContexts.end() && "Tried to find a playerId that does not exist!");

  return *(it->second);
}
