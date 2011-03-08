#ifndef MESSAGE_NUMBER_H_
#define MESSAGE_NUMBER_H_

#include <QDataStream>
#include <iostream>

class MessageNumber {
 public:
  static const MessageNumber NULL_MESSAGE;
  static const MessageNumber PLAYER_ID_CFG;
  static const MessageNumber PLAYER_ID_CNF;
  static const MessageNumber PLAYER_CONFIGURATION_CFG;
  static const MessageNumber PLAYER_CONFIGURATION_CNF;

  static const MessageNumber NO_MESSAGE;

  MessageNumber();
  MessageNumber(quint16 number, const char* name);

  operator int() const { return number; }

 protected:
  quint16 number;
  const char* name;

  friend bool operator==(const MessageNumber& lhs, const MessageNumber& rhs);
  friend QDataStream& operator>>(QDataStream& stream, MessageNumber& messageNumber);
  friend QDataStream& operator<<(QDataStream& stream, const MessageNumber& messageNumber);
  friend std::ostream& operator<<(std::ostream& stream, const MessageNumber& message);
};

bool operator==(const MessageNumber& lhs, const MessageNumber& rhs);
QDataStream& operator>>(QDataStream& stream, MessageNumber& messageNumber);
QDataStream& operator<<(QDataStream& stream, const MessageNumber& messageNumber);
  std::ostream& operator<<(std::ostream& stream, const MessageNumber& message);

#endif
