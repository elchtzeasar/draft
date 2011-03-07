#include "ConfigurationManagerImpl.h"

#include "PlayerContext.h"
#include "PlayerContextFactory.h"
#include "PlayerId.h"

#include <glog/logging.h>

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

void ConfigurationManagerImpl::createPlayerContext(const PlayerId& playerId, const QString& playerName) {
  PlayerContext* playerContext(findContext(playerId));
  if (playerContext != NULL) {
    LOG(ERROR) << "createPlayerContext called with PlayerId=" << playerId << ", "
               << "There is allready a context with that id, not doing anything.";
    return;
  }

  playerContext = playerContextFactory->createPlayerContext();

  playerContext->setPlayerName(playerName);
  playerContexts[playerId] = playerContext;
}

void ConfigurationManagerImpl::updatePlayerContext(const PlayerId& playerId, const QString& playerName) {
  PlayerContext* playerContext(findContext(playerId));
  if (playerContext == NULL) {
    LOG(ERROR) << "updatePlayerContext called with PlayerId=" << playerId << ", "
               << "there is no context for that id, not doing anything.";
    return;
  }
  
  playerContext->setPlayerName(playerName);
}

PlayerContext* ConfigurationManagerImpl::findContext(const PlayerId& playerId) const {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));
  if (it == playerContexts.end())
    return NULL;
  return it->second;
}

const PlayerContext& ConfigurationManagerImpl::getPlayerContext(const PlayerId& playerId) const {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));

  assert(it != playerContexts.end() && "Tried to find a playerId that does not exist!");

  return *(it->second);
}
