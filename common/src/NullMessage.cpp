#include "NullMessage.h"

#include <QDataStream>
#include <glog/logging.h>

#include <cassert>

using std::ostream;

NullMessage::NullMessage(quint16 messageNumber) : Message(messageNumber) {
  assert(messageNumberIsAllowed(messageNumber) && "Message number must be allowed!");
}

Message* NullMessage::clone() {
  return new NullMessage(messageNumber);
}

bool NullMessage::messageNumberIsAllowed(quint16 messageNumber) {
  return NULL_MESSAGE == messageNumber ||
         PLAYER_ID_CFG == messageNumber ||
         PLAYER_ID_CNF == messageNumber ||
         PLAYER_NAME_CNF == messageNumber;
}

bool operator==(const NullMessage& lhs, const NullMessage& rhs) {
  return lhs.messageNumber == rhs.messageNumber;
}

std::ostream& operator<<(std::ostream& stream, const NullMessage& message) {
  stream << "NullMessage { " << Message::messageNumberToString(message.messageNumber) << " }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const NullMessage&) {
  return stream;
}

QDataStream& operator>>(QDataStream& stream, NullMessage&) {
  return stream;
}
