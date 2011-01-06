#include "Message.h"

#include "NullMessage.h"
#include "PlayerNameCfgMessage.h"

#include <QDataStream>

#include <cassert>

Message::Message(quint16 messageNumber) : messageNumber(messageNumber), unused(0) {}

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
    message = new class;        	                      \
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
    PRINT_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
  }
  stream << " }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const Message& message) {
  stream << message.messageNumber;
  switch (message.messageNumber) {
    SERIALIZE_MESSAGE(NULL_MESSAGE, NullMessage);
    SERIALIZE_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
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
    DESERIALIZE_MESSAGE_PTR(PLAYER_NAME_CFG, PlayerNameCfgMessage);
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
    DESERIALIZE_MESSAGE(PLAYER_NAME_CFG, PlayerNameCfgMessage);
  default:
    assert(false && "Unkown message number!");
    break;
  }
  return stream;
}
