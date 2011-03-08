#include "AddressedMessage.h"

#include "AddressHeader.h"
#include "Message.h"
#include "NullMessage.h"
#include "PlayerConfigurationCfgMessage.h"

#include <QDataStream>

#include <cassert>

AddressedMessage::AddressedMessage() :
  header(NULL), message(NULL) {}

AddressedMessage::AddressedMessage(AddressHeader* header, Message* message) :
  header(header), message(message) {}

AddressedMessage::AddressedMessage(const AddressedMessage& original) :
  header(new AddressHeader(*original.header)),
  message(original.message->clone()) {}

AddressedMessage& AddressedMessage::operator=(const AddressedMessage& original) {
  header = new AddressHeader(*original.header);
  message = original.message->clone();

  return *this;
}

AddressedMessage::~AddressedMessage() {
  delete header;
  delete message;
}

const AddressHeader& AddressedMessage::getHeader() const {
  return *header;
}

const Message& AddressedMessage::getMessage() const {
  return *message;
}

bool operator==(const AddressedMessage& lhs, const AddressedMessage& rhs) {
  return lhs.getHeader() == rhs.getHeader() && lhs.getMessage() == rhs.getMessage();
}

std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage) {
  assert(addressedMessage.header != NULL && addressedMessage.message != NULL &&
	 "Cannot print without an allocated header/message...");
  stream << "AddressedMessage { " << *addressedMessage.header << ", ";
  stream << *addressedMessage.message << '}';
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage) {
  assert(addressedMessage.header != NULL && addressedMessage.message != NULL &&
	 "Cannot deserialize without an allocated header/message...");
  stream << *addressedMessage.header << *addressedMessage.message;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage) {
  assert(addressedMessage.header == NULL && addressedMessage.message == NULL &&
	 "Cannot deserialize into an allocated header/message...");

  addressedMessage.header = new AddressHeader;
  stream >> *addressedMessage.header;
  stream >> addressedMessage.message;
  return stream;
}
