#ifndef ADDRESS_HEADER_H_
#define ADDRESS_HEADER_H_

#include <QtGlobal>

#include <iostream>

class QDataStream;

class AddressHeader {
 public:
  AddressHeader();
  AddressHeader(const AddressHeader& original);
  AddressHeader& operator=(AddressHeader& original);

 private:
  quint32 version;
  quint8 reserved1;
  quint8 reserved2;
  quint8 reserved3;
  quint8 reserved4;

  friend std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);
};

std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);

#endif // ADDRESS_HEADER_H_
