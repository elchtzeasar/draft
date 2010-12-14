#include "NullMessage.h"

#include <QDataStream>

using std::ostream;

std::ostream& operator<<(std::ostream& stream, const Message& message) {
  stream << "NullMessage {}";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const Message& message) {
  return stream;
}

QDataStream& operator>>(QDataStream& stream, Message& message) {
  return stream;
}
