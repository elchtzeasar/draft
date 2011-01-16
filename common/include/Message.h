#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <QtGlobal>

#include <iostream>
#include <cassert>

class QDataStream;

enum {
  NULL_MESSAGE,
  PLAYER_ID_CFG,
  PLAYER_ID_CNF,
  PLAYER_NAME_CFG,
  PLAYER_NAME_CNF,

  NO_MESSAGE = 0xff
};

class Message {
 public:
  Message(quint16 messageNumber);
  virtual ~Message() {}

  virtual Message* clone() = 0;

  quint16 getMessageNumber() const;
  template<typename T>
  const T& to() const {
    assert(T::messageNumberIsAllowed(messageNumber) && "Casting message to wrong type!");
    return *static_cast<const T*>(this);
  }

  // TODO: The message numbers should be a class containing a toString function instead:
  static const char* messageNumberToString(quint16 messageNumber);

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
