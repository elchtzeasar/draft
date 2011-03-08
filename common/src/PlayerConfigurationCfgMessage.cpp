#include "PlayerConfigurationCfgMessage.h"

#include <QDataStream>
#include <glog/logging.h>

#include <cstring>
#include <cstdlib>

PlayerConfigurationCfgMessage::PlayerConfigurationCfgMessage(const MessageNumber& messageNumber) :
  Message(messageNumber), unused(0), playerName(const_cast<char*>("default message")) {
  assert(messageNumberIsAllowed(messageNumber) && "Message number must be allowed!");
}

PlayerConfigurationCfgMessage::PlayerConfigurationCfgMessage(const char* playerName) :
  Message(MessageNumber::PLAYER_CONFIGURATION_CFG), unused(0),
  playerName(static_cast<char*>(malloc(strlen(playerName) + 1))) {
  strcpy(this->playerName, playerName);
}

Message* PlayerConfigurationCfgMessage::clone() {
  return new PlayerConfigurationCfgMessage(playerName);
}

bool PlayerConfigurationCfgMessage::messageNumberIsAllowed(const MessageNumber& messageNumber) {
  return MessageNumber::PLAYER_CONFIGURATION_CFG == messageNumber;
}

const char* PlayerConfigurationCfgMessage::getPlayerName() const {
  return playerName;
}

bool operator==(const PlayerConfigurationCfgMessage& lhs, const PlayerConfigurationCfgMessage& rhs) {
  return strcmp(lhs.playerName, rhs.playerName) == 0;
}

std::ostream& operator<<(std::ostream& stream, const PlayerConfigurationCfgMessage& message) {
  stream << "PlayerConfigurationCfgMessage { playerName='" << message.playerName << "' }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const PlayerConfigurationCfgMessage& message) {
  stream.writeBytes(message.playerName, strlen(message.playerName));

  return stream;
}

QDataStream& operator>>(QDataStream& stream, PlayerConfigurationCfgMessage& message) {
  unsigned int noBytes(0);
  stream.readBytes(message.playerName, noBytes);

  return stream;
}
