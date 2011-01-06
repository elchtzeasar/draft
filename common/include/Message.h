#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QtGlobal>

#include <iostream>
#include <cassert>
class QDataStream;

enum {
  NULL_MESSAGE,
  PLAYER_NAME_CFG,

  NO_MESSAGE = 0xff
};

class Message {
 public:
  Message(quint16 messageNumber);
  virtual ~Message() {}

  virtual Message* clone() = 0;

  template<typename T>
  const T& to() const {
    assert(messageNumber == T::MESSAGE_NUMBER && "Casting message to wrong type!");
    return *static_cast<const T*>(this);
  }

 protected:
  quint16 messageNumber;
  // The following is needed to fill the class up to an even amount of 32 bits:
  const quint16 unused;

  friend std::ostream& operator<<(std::ostream& stream, const Message& message);
  friend QDataStream& operator<<(QDataStream& stream, const Message& message);
  friend QDataStream& operator>>(QDataStream& stream, Message*& message);
  friend QDataStream& operator>>(QDataStream& stream, Message& message);
};

std::ostream& operator<<(std::ostream& stream, const Message& message);
QDataStream& operator<<(QDataStream& stream, const Message& message);
QDataStream& operator>>(QDataStream& stream, Message*& message);
QDataStream& operator>>(QDataStream& stream, Message& message);

#endif // MESSAGE_H_
