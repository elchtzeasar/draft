#ifndef ADDRESS_HEADER_H_
#define ADDRESS_HEADER_H_

#include <QtGlobal>

#include <iostream>

class QDataStream;

class AddressHeader {
 public:
  AddressHeader();
  AddressHeader(quint8 sentFromPlayerId, quint8 sentToPlayerId);

  AddressHeader(const AddressHeader& original);
  AddressHeader& operator=(AddressHeader& original);

  quint8 getSenderPlayerId() const;
  quint8 getReceiverPlayerId() const;

  static const quint8 NO_PLAYER_ID;
  static const quint8 SERVER_PLAYER_ID;
  static const quint8 OWN_PLAYER_ID;

 private:
  quint32 version;
  quint8 sentFromPlayerId;
  quint8 sentToPlayerId;
  quint8 reserved1;
  quint8 reserved2;

  friend std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);
};

std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);

#endif // ADDRESS_HEADER_H_
