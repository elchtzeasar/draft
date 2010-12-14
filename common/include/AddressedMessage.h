#ifndef ADDRESSED_MESSAGE_H_
#define ADDRESSED_MESSAGE_H_

class AddressHeader;
class Message;

class QDataStream;

#include <iostream>

class AddressedMessage {
 public:
  AddressedMessage();
  AddressedMessage(AddressHeader* header, Message* message);
  ~AddressedMessage();

 private:
  AddressHeader* header;
  Message* message;

  friend std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage);
  friend QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage);
  friend QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage);
};

std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage);
QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage);
QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage);

#endif // ADDRESSED_MESSAGE_H_
