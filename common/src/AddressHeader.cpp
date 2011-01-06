#include "AddressHeader.h"

#include <QDataStream>

using std::ostream;

AddressHeader::AddressHeader() :
  version(1),
  reserved1(0),
  reserved2(0),
  reserved3(0),
  reserved4(0) {}

AddressHeader::AddressHeader(const AddressHeader& original) :
  version(original.version),
  reserved1(original.reserved1),
  reserved2(original.reserved2),
  reserved3(original.reserved3),
  reserved4(original.reserved4) {}

AddressHeader& AddressHeader::operator=(AddressHeader& original) {
  version = original.version;
  reserved1 = original.reserved1;
  reserved2 = original.reserved2;
  reserved3 = original.reserved3;
  reserved4 = original.reserved4;

  return *this;
}

ostream& operator<<(ostream& stream, const AddressHeader& addressHeader) {
  stream << "AddressHeader { version=" << addressHeader.version << " }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader) {
  stream << addressHeader.version
	 << addressHeader.reserved1 << addressHeader.reserved2
	 << addressHeader.reserved3 << addressHeader.reserved4;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader) {
  stream >> addressHeader.version
	 >> addressHeader.reserved1 >> addressHeader.reserved2
	 >> addressHeader.reserved3 >> addressHeader.reserved4;
  return stream;
}
