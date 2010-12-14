#include "AddressHeader.h"

#include <QDataStream>

using std::ostream;

AddressHeader::AddressHeader() :
  version(0xffffffff),
  intendedFor(0xff),
  reserved1(0),
  reserved2(0),
  reserved3(0) {}

AddressHeader::AddressHeader(quint32 version, quint8 intendedFor) :
  version(version),
  intendedFor(intendedFor),
  reserved1(0),
  reserved2(0),
  reserved3(0) {}

ostream& operator<<(ostream& stream, const AddressHeader& addressHeader) {
  stream << "AddressHeader { version=" << addressHeader.version << ", "
	 << "intendedFor=" << addressHeader.intendedFor << '}';
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader) {
  stream << addressHeader.version << addressHeader.intendedFor
	 << addressHeader.reserved1 << addressHeader.reserved2 << addressHeader.reserved3;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader) {
  stream >> (addressHeader.version) >> addressHeader.intendedFor
	 >> addressHeader.reserved1 >> addressHeader.reserved2 >> addressHeader.reserved3;
  return stream;
}
