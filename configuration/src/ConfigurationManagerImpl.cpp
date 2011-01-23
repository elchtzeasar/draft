#include "ConfigurationManagerImpl.h"

#include "AddressHeader.h"
#include "PlayerContext.h"
#include "PlayerContextFactory.h"

#include <cassert>

using std::map;

ConfigurationManagerImpl::ConfigurationManagerImpl(PlayerContext* ownPlayerContext, PlayerContextFactory* playerContextFactory) :
  playerContextFactory(playerContextFactory) {
  playerContexts[AddressHeader::OWN_PLAYER_ID] = ownPlayerContext;
}

ConfigurationManagerImpl::~ConfigurationManagerImpl() {
  for (PlayerContextMap::iterator it(playerContexts.begin());
       it != playerContexts.end();
       ++it) {
    // TODO: The following assumes that the own player id is set, otherwise the own
    //       player context will not be deleted:
    if (it->first != AddressHeader::OWN_PLAYER_ID) {
      delete it->second;
    }
    it->second = NULL;
  }

  delete playerContextFactory;
}

void ConfigurationManagerImpl::setOwnPlayerId(quint8 playerId) {
  PlayerContext* ownPlayerContext = playerContexts[AddressHeader::OWN_PLAYER_ID];
  playerContexts[playerId] = ownPlayerContext;
}

void ConfigurationManagerImpl::setPlayerContext(quint8 playerId, const std::string& playerName) {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));
  PlayerContext* playerContext(NULL);
  if (it == playerContexts.end())
    playerContext = playerContextFactory->createPlayerContext();
  else
    playerContext = it->second;

  playerContext->setPlayerName(playerName);
  playerContexts[playerId] = playerContext;
}

#include <iostream>
const PlayerContext& ConfigurationManagerImpl::getPlayerContext(quint8 playerId) const {
  PlayerContextMap::const_iterator it(playerContexts.find(playerId));

  assert(it != playerContexts.end() && "Tried to find a playerId that does not exist!");

  return *(it->second);
}
