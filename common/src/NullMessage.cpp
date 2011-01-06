#include "NullMessage.h"

#include <QDataStream>

using std::ostream;

NullMessage::NullMessage() : Message(NULL_MESSAGE) {}

Message* NullMessage::clone() {
  return new NullMessage;
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

const quint16 NullMessage::MESSAGE_NUMBER(NULL_MESSAGE);
