#include "PlayerNameCfgMessage.h"

#include <QDataStream>
#include <glog/logging.h>

#include <cstring>
#include <cstdlib>

PlayerNameCfgMessage::PlayerNameCfgMessage(const MessageNumber& messageNumber) :
  Message(messageNumber), unused(0), playerName(const_cast<char*>("default message")) {
  assert(messageNumberIsAllowed(messageNumber) && "Message number must be allowed!");
}

PlayerNameCfgMessage::PlayerNameCfgMessage(const char* playerName) :
  Message(MessageNumber::PLAYER_NAME_CFG), unused(0),
  playerName(static_cast<char*>(malloc(strlen(playerName) + 1))) {
  strcpy(this->playerName, playerName);
}

Message* PlayerNameCfgMessage::clone() {
  return new PlayerNameCfgMessage(playerName);
}

bool PlayerNameCfgMessage::messageNumberIsAllowed(const MessageNumber& messageNumber) {
  return MessageNumber::PLAYER_NAME_CFG == messageNumber;
}

const char* PlayerNameCfgMessage::getPlayerName() const {
  return playerName;
}

bool operator==(const PlayerNameCfgMessage& lhs, const PlayerNameCfgMessage& rhs) {
  return strcmp(lhs.playerName, rhs.playerName) == 0;
}

std::ostream& operator<<(std::ostream& stream, const PlayerNameCfgMessage& message) {
  stream << "PlayerNameCfgMessage { playerName='" << message.playerName << "' }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const PlayerNameCfgMessage& message) {
  stream.writeBytes(message.playerName, strlen(message.playerName));

  return stream;
}

QDataStream& operator>>(QDataStream& stream, PlayerNameCfgMessage& message) {
  unsigned int noBytes(0);
  stream.readBytes(message.playerName, noBytes);

  return stream;
}
