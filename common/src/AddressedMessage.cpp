#include "AddressedMessage.h"

#include "AddressHeader.h"
#include "Message.h"
#include "NullMessage.h"

#include <QDataStream>

AddressedMessage::AddressedMessage() :
  header(new AddressHeader), message(NULL) {}

AddressedMessage::AddressedMessage(AddressHeader* header, Message* message) :
  header(header), message(message) {}

AddressedMessage::~AddressedMessage() {
  delete header;
  delete message;
}

std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage) {
  stream << "AddressedMessage { " << *addressedMessage.header << ", "
         << *addressedMessage.message << '}';
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage) {
  stream << *addressedMessage.header << *addressedMessage.message;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage) {
  stream >> *addressedMessage.header;
  if (addressedMessage.message == NULL)
    addressedMessage.message = new NullMessage;
  stream >> *addressedMessage.message;
  return stream;
}


