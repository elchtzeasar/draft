#include "PlayerContextFactoryImpl.h"

#include "PlayerContextImpl.h"

PlayerContextFactoryImpl::~PlayerContextFactoryImpl() {}

PlayerContext* PlayerContextFactoryImpl::createPlayerContext() {
  return new PlayerContextImpl;
}
