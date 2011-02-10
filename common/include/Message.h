#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "MessageNumber.h"

#include <QtGlobal>

#include <iostream>
#include <cassert>

class QDataStream;

class Message {
 public:
  Message(MessageNumber messageNumber);
  virtual ~Message() {}

  virtual Message* clone() = 0;

  MessageNumber getMessageNumber() const;
  template<typename T>
  const T& to() const {
    assert(T::messageNumberIsAllowed(messageNumber) && "Casting message to wrong type!");
    return *static_cast<const T*>(this);
  }

  // TODO: The message numbers should be a class containing a toString function instead:
  static const char* messageNumberToString(const MessageNumber& messageNumber);

 protected:
  MessageNumber messageNumber;
  // The following is needed to fill the class up to an even amount of 32 bits:
  const quint16 unused;

  friend std::ostream& operator<<(std::ostream& stream, const Message& message);
  friend QDataStream& operator<<(QDataStream& stream, const Message& message);
  friend QDataStream& operator>>(QDataStream& stream, Message*& message);
  friend QDataStream& operator>>(QDataStream& stream, Message& message);
};

bool operator==(const Message& lhs, const Message& rhs);

std::ostream& operator<<(std::ostream& stream, const Message& message);
QDataStream& operator<<(QDataStream& stream, const Message& message);
QDataStream& operator>>(QDataStream& stream, Message*& message);
QDataStream& operator>>(QDataStream& stream, Message& message);

#endif // MESSAGE_H_
