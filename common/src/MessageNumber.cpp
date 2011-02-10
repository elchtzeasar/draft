#include "MessageNumber.h"

#include <QtGlobal>

using std::ostream;

MessageNumber::MessageNumber(quint16 number, const char* name) :
  number(number), name(name) {}

bool operator==(const MessageNumber& lhs, const MessageNumber& rhs) {
  return lhs.number == rhs.number;
}

QDataStream& operator>>(QDataStream& stream, MessageNumber& messageNumber) {
  stream >> messageNumber.number;

  return stream;
}

QDataStream& operator<<(QDataStream& stream, const MessageNumber& messageNumber) {
  stream << messageNumber.number;

  return stream;
}

ostream& operator<<(ostream& stream, const MessageNumber& message) {
  stream << message.name;

  return stream;
}

const MessageNumber::MessageNumber NULL_MESSAGE(0, "NullMessage");
const MessageNumber::MessageNumber PLAYER_ID_CFG(1, "PlayerIdCfg");
const MessageNumber::MessageNumber PLAYER_ID_CNF(2, "PlayerIdCnf");
const MessageNumber::MessageNumber PLAYER_NAME_CFG(3, "PlayerNameCfg");
const MessageNumber::MessageNumber PLAYER_NAME_CNF(4, "PlayerNameCnf");

const MessageNumber::MessageNumber NO_MESSAGE(0xff, "NoMessage");
