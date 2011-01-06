#ifndef ADDRESSED_MESSAGE_H_
#define ADDRESSED_MESSAGE_H_

class AddressHeader;
class Message;

class QDataStream;

#include <QMetaType>

#include <iostream>

class AddressedMessage {
 public:
  AddressedMessage();
  AddressedMessage(AddressHeader* header, Message* message);

  AddressedMessage(const AddressedMessage& original);
  AddressedMessage& operator=(AddressedMessage& original);

  ~AddressedMessage();

  const AddressHeader& getHeader() const;
  const Message& getMessage() const;

 private:
  AddressHeader* header;
  Message* message;

  friend std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage);
  friend QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage);
  friend QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage);
};

Q_DECLARE_METATYPE(AddressedMessage);

std::ostream& operator<<(std::ostream& stream, const AddressedMessage& addressedMessage);
QDataStream& operator<<(QDataStream& stream, const AddressedMessage& addressedMessage);
QDataStream& operator>>(QDataStream& stream, AddressedMessage& addressedMessage);

#endif // ADDRESSED_MESSAGE_H_
