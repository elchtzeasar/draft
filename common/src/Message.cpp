#include "Message.h"

#include "NullMessage.h"
#include "PlayerNameCfgMessage.h"

#include <QDataStream>
#include <glog/logging.h>

#include <cassert>

Message::Message(quint16 messageNumber) : messageNumber(messageNumber), unused(0) {}

quint16 Message::getMessageNumber() const {
  return messageNumber;
}

const char* Message::messageNumberToString(quint16 messageNumber) {
  switch (messageNumber) {
  case NULL_MESSAGE:
    return "NullMessage";
    break;
  case PLAYER_NAME_CFG:
    return "PlayerNameCfg";
    break;
  case PLAYER_NAME_CNF:
    return "PlayerNameCnf";
    break;
  case PLAYER_ID_CFG:
    return "PlayerIdCfg";
    break;
  case PLAYER_ID_CNF:
    return "PlayerIdCnf";
    break;
  case NO_MESSAGE:
    return "NO_MESSAGE";
    break;
  default:
    return "UnkownMessage";
  }
}

#define PRINT_MESSAGE(expectedMessageNumber, class)     \
  case expectedMessageNumber:                           \
    stream << static_cast<const class&>(message);       \
    break;

#define SERIALIZE_MESSAGE(expectedMessageNumber, class) \
  case expectedMessageNumber:		                \
    stream << dynamic_cast<const class&>(message);      \
    break;		                                \
 
#define DESERIALIZE_MESSAGE_PTR(expectedMessageNumber, class) \
  case expectedMessageNumber:                                 \
    message = new class(expectedMessageNumber);               \
    stream >> *dynamic_cast<class*>(message);                 \
    break;

#define DESERIALIZE_MESSAGE(expectedMessageNumber, class) \
  case expectedMessageNumber:                             \
    stream >> static_cast<class&>(message);               \
    break;

std::ostream& operator<<(std::ostream& stream, const Message& message) {
  stream << "Message { messageNumber=" << message.messageNumber << " => ";
  switch (message.messageNumber) {
    PRINT_MESSAGE(NULL_MESSAGE, NullMessage);
    PRINT_MESSAGE(PLAYER_ID_CFG, NullMessage);
    PRINT_MESSAGE(PLAYER_ID_CNF, NullMessage);
    PRINT_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
    PRINT_MESSAGE(PLAYER_NAME_CNF, NullMessage);
  default:
    assert(false && "Unkown message number!");
    break;
  }
  stream << " }";
  return stream;
}

bool operator==(const Message& lhs, const Message& rhs) {
  if (lhs.getMessageNumber() == rhs.getMessageNumber()) {
    switch (lhs.getMessageNumber()) {
    case NULL_MESSAGE:
    case PLAYER_ID_CNF:
    case PLAYER_NAME_CNF:
    case PLAYER_ID_CFG:
      return static_cast<const NullMessage&>(lhs) ==
	static_cast<const NullMessage&>(rhs);
    case PLAYER_NAME_CFG:
      return static_cast<const PlayerNameCfgMessage&>(lhs) ==
	static_cast<const PlayerNameCfgMessage&>(rhs);
    }
  }
  return false;
}

QDataStream& operator<<(QDataStream& stream, const Message& message) {
  stream << message.messageNumber;
  switch (message.messageNumber) {
    SERIALIZE_MESSAGE(NULL_MESSAGE, NullMessage);
    SERIALIZE_MESSAGE(PLAYER_ID_CFG, NullMessage);
    SERIALIZE_MESSAGE(PLAYER_ID_CNF, NullMessage);
    SERIALIZE_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
    SERIALIZE_MESSAGE(PLAYER_NAME_CNF, NullMessage);
  default:
    assert(false && "Unkown message number!");
    break;
  }
  return stream;
}

QDataStream& operator>>(QDataStream& stream, Message*& message) {
  quint16 messageNumber(0);
  stream >> messageNumber;
  switch (messageNumber) {
    DESERIALIZE_MESSAGE_PTR(NULL_MESSAGE, NullMessage);
    DESERIALIZE_MESSAGE_PTR(PLAYER_ID_CFG, NullMessage);
    DESERIALIZE_MESSAGE_PTR(PLAYER_ID_CNF, NullMessage);
    DESERIALIZE_MESSAGE_PTR(PLAYER_NAME_CFG, PlayerNameCfgMessage);
    DESERIALIZE_MESSAGE_PTR(PLAYER_NAME_CNF, NullMessage);
  default:
    assert(false && "Unkown message number!");
    break;
  }
  return stream;
}

QDataStream& operator>>(QDataStream& stream, Message& message) {
  stream >> message.messageNumber;
  switch (message.messageNumber) {
    DESERIALIZE_MESSAGE(NULL_MESSAGE, NullMessage);
    DESERIALIZE_MESSAGE(PLAYER_ID_CFG, NullMessage);
    DESERIALIZE_MESSAGE(PLAYER_ID_CNF, NullMessage);
    DESERIALIZE_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
    DESERIALIZE_MESSAGE(PLAYER_NAME_CNF, NullMessage);
  default:
    assert(false && "Unkown message number!");
    break;
  }
  return stream;
}
