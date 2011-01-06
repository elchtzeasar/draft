#include "PlayerNameCfgMessage.h"

#include <QDataStream>

#include <cstring>
#include <cstdlib>

PlayerNameCfgMessage::PlayerNameCfgMessage() :
  Message(PLAYER_NAME_CFG), unused(0), playerName(const_cast<char*>("default message")) {}

PlayerNameCfgMessage::PlayerNameCfgMessage(const char* playerName) :
  Message(PLAYER_NAME_CFG), unused(0),
  playerName(static_cast<char*>(malloc(strlen(playerName) + 1))) {
  strcpy(this->playerName, playerName);
}

Message* PlayerNameCfgMessage::clone() {
  return new PlayerNameCfgMessage(playerName);
}

const char* PlayerNameCfgMessage::getPlayerName() const {
  return playerName;
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

const quint16 PlayerNameCfgMessage::MESSAGE_NUMBER(PLAYER_NAME_CFG);
