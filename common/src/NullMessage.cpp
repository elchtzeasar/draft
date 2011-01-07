#include "NullMessage.h"

#include <QDataStream>

using std::ostream;

NullMessage::NullMessage() : Message(NULL_MESSAGE) {}

Message* NullMessage::clone() {
  return new NullMessage;
}

bool NullMessage::messageNumberIsAllowed(quint16 messageNumber) {
  return NULL_MESSAGE == messageNumber;
}

std::ostream& operator<<(std::ostream& stream, const NullMessage&) {
  stream << "NullMessage { }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const NullMessage&) {
  return stream;
}

QDataStream& operator>>(QDataStream& stream, NullMessage&) {
  return stream;
}
