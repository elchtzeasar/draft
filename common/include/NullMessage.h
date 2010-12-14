#ifndef NULL_MESSAGE_H_
#define NULL_MESSAGE_H_

#include "Message.h"

class NullMessage : public Message {
 public:
  NullMessage() {}

  friend std::ostream& operator<<(std::ostream& stream, const Message& message);
  friend QDataStream& operator<<(QDataStream& stream, const Message& message);
  friend QDataStream& operator>>(QDataStream& stream, Message& message);
};

std::ostream& operator<<(std::ostream& stream, const Message& message);
QDataStream& operator<<(QDataStream& stream, const Message& message);
QDataStream& operator>>(QDataStream& stream, Message& message);

#endif // NULL_MESSAGE_H_
