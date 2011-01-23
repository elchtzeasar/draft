#ifndef ADDRESS_HEADER_H_
#define ADDRESS_HEADER_H_

#include "PlayerId.h"

#include <QtGlobal>

#include <iostream>

class QDataStream;

class AddressHeader {
 public:
  AddressHeader();
  AddressHeader(const PlayerId& sentFromPlayerId, const PlayerId& sentToPlayerId);

  AddressHeader(const AddressHeader& original);
  AddressHeader& operator=(AddressHeader& original);

  const PlayerId& getSenderPlayerId() const;
  const PlayerId& getReceiverPlayerId() const;

 private:
  quint32 version;
  PlayerId sentFromPlayerId;
  PlayerId sentToPlayerId;
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
