#include "Message.h"

#include "NullMessage.h"
#include "PlayerNameCfgMessage.h"

#include <QDataStream>
#include <glog/logging.h>

#include <cassert>

Message::Message(MessageNumber messageNumber) : messageNumber(messageNumber), unused(0) {}

MessageNumber Message::getMessageNumber() const {
  return messageNumber;
}

const char* Message::messageNumberToString(const MessageNumber& messageNumber) {
  if (messageNumber == MessageNumber::NULL_MESSAGE) {
    return "NullMessage";
  } else if (messageNumber == MessageNumber::PLAYER_NAME_CFG) {
    return "PlayerNameCfg";
  } else if (messageNumber == MessageNumber::PLAYER_NAME_CNF) {
    return "PlayerNameCnf";
  } else if (messageNumber == MessageNumber::PLAYER_ID_CFG) {
    return "PlayerIdCfg";
  } else if (messageNumber == MessageNumber::PLAYER_ID_CNF) {
    return "PlayerIdCnf";
  } else if (messageNumber == MessageNumber::NO_MESSAGE) {
    return "NO_MESSAGE";
  } else {
    return "UnkownMessage";
  }
}

#define PRINT_MESSAGE(expectedMessageNumber, class)     \
  if (message.messageNumber == expectedMessageNumber) {	\
    stream << static_cast<const class&>(message);       \
  }

#define SERIALIZE_MESSAGE(expectedMessageNumber, class) \
  if (message.messageNumber == expectedMessageNumber) {	\
    stream << dynamic_cast<const class&>(message);      \
  }
 
#define DESERIALIZE_MESSAGE_PTR(expectedMessageNumber, class) \
  if (messageNumber == expectedMessageNumber) {      \
    message = new class(expectedMessageNumber);               \
    stream >> *dynamic_cast<class*>(message);                 \
  }

#define DESERIALIZE_MESSAGE(expectedMessageNumber, class) \
  if (message.messageNumber == expectedMessageNumber) {	  \
    stream >> static_cast<class&>(message);               \
  }

std::ostream& operator<<(std::ostream& stream, const Message& message) {
  stream << "Message { messageNumber=" << message.messageNumber << " => ";
  PRINT_MESSAGE(MessageNumber::NULL_MESSAGE, NullMessage) else
  PRINT_MESSAGE(MessageNumber::PLAYER_ID_CFG, NullMessage) else
  PRINT_MESSAGE(MessageNumber::PLAYER_ID_CNF, NullMessage) else
  PRINT_MESSAGE(MessageNumber::PLAYER_NAME_CFG, PlayerNameCfgMessage) else
  PRINT_MESSAGE(MessageNumber::PLAYER_NAME_CNF, NullMessage) else {
    assert(false && "Unkown message number!");
  }
  stream << " }";
  return stream;
}

bool operator==(const Message& lhs, const Message& rhs) {
  if (lhs.getMessageNumber() == rhs.getMessageNumber()) {
    if (lhs.getMessageNumber() == MessageNumber::NULL_MESSAGE ||
	lhs.getMessageNumber() == MessageNumber::PLAYER_ID_CNF ||
	lhs.getMessageNumber() == MessageNumber::PLAYER_NAME_CNF ||
	lhs.getMessageNumber() == MessageNumber::PLAYER_ID_CFG) {
      return static_cast<const NullMessage&>(lhs) ==
	static_cast<const NullMessage&>(rhs);
    } else if(lhs.getMessageNumber() == MessageNumber::PLAYER_NAME_CFG) {
      return static_cast<const PlayerNameCfgMessage&>(lhs) ==
	static_cast<const PlayerNameCfgMessage&>(rhs);
    } else {
      assert(false && "Received message with unknown MessageNumber");
    }
  }
  return false;
}

QDataStream& operator<<(QDataStream& stream, const Message& message) {
  stream << message.messageNumber;

  SERIALIZE_MESSAGE(MessageNumber::NULL_MESSAGE, NullMessage) else
  SERIALIZE_MESSAGE(MessageNumber::PLAYER_ID_CFG, NullMessage) else
  SERIALIZE_MESSAGE(MessageNumber::PLAYER_ID_CNF, NullMessage) else
  SERIALIZE_MESSAGE(MessageNumber::PLAYER_NAME_CFG, PlayerNameCfgMessage) else
  SERIALIZE_MESSAGE(MessageNumber::PLAYER_NAME_CNF, NullMessage) else {
    assert(false && "Unkown message number!");
  }
  return stream;
}

QDataStream& operator>>(QDataStream& stream, Message*& message) {
  MessageNumber messageNumber;
  stream >> messageNumber;

  DESERIALIZE_MESSAGE_PTR(MessageNumber::NULL_MESSAGE, NullMessage) else
  DESERIALIZE_MESSAGE_PTR(MessageNumber::PLAYER_ID_CFG, NullMessage) else
  DESERIALIZE_MESSAGE_PTR(MessageNumber::PLAYER_ID_CNF, NullMessage) else
  DESERIALIZE_MESSAGE_PTR(MessageNumber::PLAYER_NAME_CFG, PlayerNameCfgMessage) else
  DESERIALIZE_MESSAGE_PTR(MessageNumber::PLAYER_NAME_CNF, NullMessage) else {
    LOG(ERROR) << "MessageNumber=" << messageNumber;
    assert(false && "Unkown message number!");
  }
  return stream;
}

QDataStream& operator>>(QDataStream& stream, Message& message) {
  stream >> message.messageNumber;

  DESERIALIZE_MESSAGE(MessageNumber::NULL_MESSAGE, NullMessage) else
  DESERIALIZE_MESSAGE(MessageNumber::PLAYER_ID_CFG, NullMessage) else
  DESERIALIZE_MESSAGE(MessageNumber::PLAYER_ID_CNF, NullMessage) else
  DESERIALIZE_MESSAGE(MessageNumber::PLAYER_NAME_CFG, PlayerNameCfgMessage) else
  DESERIALIZE_MESSAGE(MessageNumber::PLAYER_NAME_CNF, NullMessage) else {
    assert(false && "Unkown message number!");
  }
  return stream;
}
