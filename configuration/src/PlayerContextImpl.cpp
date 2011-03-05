#include "PlayerContextImpl.h"

PlayerContextImpl::PlayerContextImpl() : playerName("Unknown player") {}

PlayerContextImpl::~PlayerContextImpl() {
}

const QString& PlayerContextImpl::getPlayerName() const {
  return playerName;
}

void PlayerContextImpl::setPlayerName(const QString& playerName) {
  this->playerName = playerName;
}
