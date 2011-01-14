#include "PlayerContextImpl.h"

PlayerContextImpl::PlayerContextImpl() : playerName("Unknown player") {}

PlayerContextImpl::~PlayerContextImpl() {
}

const std::string& PlayerContextImpl::getPlayerName() const {
  return playerName;
}

void PlayerContextImpl::setPlayerName(const std::string& playerName) {
  this->playerName = playerName;
}
