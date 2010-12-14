#ifndef ADDRESS_HEADER_H_
#define ADDRESS_HEADER_H_

#include <QtGlobal>

#include <iostream>

class QDataStream;

class AddressHeader {
 public:
  AddressHeader();
  AddressHeader(quint32 version, quint8 intendedFor);

 private:
  AddressHeader(const AddressHeader&);
  AddressHeader& operator=(AddressHeader&);

  quint32 version;
  quint8 intendedFor;
  quint8 reserved1;
  quint8 reserved2;
  quint8 reserved3;

  friend std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
  friend QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);
};

std::ostream& operator<<(std::ostream& stream, const AddressHeader& addressHeader);
QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader);
QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader);

#endif // ADDRESS_HEADER_H_
