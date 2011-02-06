#ifndef NULL_MESSAGE_H_
#define NULL_MESSAGE_H_

#include "Message.h"

class NullMessage : public Message {
 public:
  NullMessage(quint16 messageNumber);

  virtual Message* clone();
  static bool messageNumberIsAllowed(quint16 messageNumber);

 private:
  friend bool operator==(const NullMessage& lhs, const NullMessage& rhs);
  friend std::ostream& operator<<(std::ostream& stream, const NullMessage& message);
  friend QDataStream& operator<<(QDataStream& stream, const NullMessage& message);
  friend QDataStream& operator>>(QDataStream& stream, NullMessage& message);
};

bool operator==(const NullMessage& lhs, const NullMessage& rhs);
std::ostream& operator<<(std::ostream& stream, const NullMessage& message);
QDataStream& operator<<(QDataStream& stream, const NullMessage& message);
QDataStream& operator>>(QDataStream& stream, NullMessage& message);

#endif // NULL_MESSAGE_H_
