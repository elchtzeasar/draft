#include "MessageNumber.h"

#include <QtGlobal>
#include <glog/logging.h>

using std::ostream;

static const char* NO_MESSAGE_NAME("NoMessage");

enum {
  NULL_MESSAGE_NUMBER,
  PLAYER_ID_CFG_NUMBER,
  PLAYER_ID_CNF_NUMBER,
  PLAYER_NAME_CFG_NUMBER,
  PLAYER_NAME_CNF_NUMBER,
 
  NO_MESSAGE_NUMBER = 0xff
};

MessageNumber::MessageNumber() :
  number(NO_MESSAGE_NUMBER), name(NO_MESSAGE_NAME) {}

MessageNumber::MessageNumber(quint16 number, const char* name) :
  number(number), name(name) {}

bool operator==(const MessageNumber& lhs, const MessageNumber& rhs) {
  return lhs.number == rhs.number;
}

QDataStream& operator>>(QDataStream& stream, MessageNumber& messageNumber) {
  quint16 number;
  stream >> number;

  switch (number) {
  case NULL_MESSAGE_NUMBER:
    messageNumber = MessageNumber::NULL_MESSAGE;
    break;
  case PLAYER_ID_CFG_NUMBER:
    messageNumber = MessageNumber::PLAYER_ID_CFG;
    break;
  case PLAYER_ID_CNF_NUMBER:
    messageNumber = MessageNumber::PLAYER_ID_CNF;
    break;
  case PLAYER_NAME_CFG_NUMBER:
    messageNumber = MessageNumber::PLAYER_NAME_CFG;
    break;
  case PLAYER_NAME_CNF_NUMBER:
    messageNumber = MessageNumber::PLAYER_NAME_CNF;
    break;
  case NO_MESSAGE_NUMBER:
    LOG(ERROR) << "Deserialized message number: " << number << " (NoMessage)";
    messageNumber = MessageNumber::NO_MESSAGE;
    break;
  default:
    LOG(ERROR) << "Deserialized message number: " << number << ". This should not be possible";
    messageNumber = MessageNumber::NO_MESSAGE;
  }

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

const MessageNumber MessageNumber::NULL_MESSAGE(0, "NullMessage");
const MessageNumber MessageNumber::PLAYER_ID_CFG(1, "PlayerIdCfg");
const MessageNumber MessageNumber::PLAYER_ID_CNF(2, "PlayerIdCnf");
const MessageNumber MessageNumber::PLAYER_NAME_CFG(3, "PlayerNameCfg");
const MessageNumber MessageNumber::PLAYER_NAME_CNF(4, "PlayerNameCnf");

const MessageNumber MessageNumber::NO_MESSAGE(NO_MESSAGE_NUMBER, NO_MESSAGE_NAME);
