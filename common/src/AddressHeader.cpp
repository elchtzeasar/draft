#include "AddressHeader.h"

#include <QDataStream>

#include <cassert>

using std::ostream;

static quint32 VERSION_NUMBER(1);

AddressHeader::AddressHeader() :
  version(VERSION_NUMBER),
  sentFromPlayerId(NO_PLAYER_ID),
  sentToPlayerId(NO_PLAYER_ID),
  reserved1(0),
  reserved2(0) {}

AddressHeader::AddressHeader(quint8 sentFromPlayerId, quint8 sentToPlayerId) :
  version(VERSION_NUMBER),
  sentFromPlayerId(sentFromPlayerId),
  sentToPlayerId(sentToPlayerId),
  reserved1(0),
  reserved2(0) {}

AddressHeader::AddressHeader(const AddressHeader& original) :
  version(original.version),
  sentFromPlayerId(original.sentFromPlayerId),
  sentToPlayerId(original.sentToPlayerId),
  reserved1(original.reserved1),
  reserved2(original.reserved2) {}

AddressHeader& AddressHeader::operator=(AddressHeader& original) {
  version = original.version;
  sentFromPlayerId = original.sentFromPlayerId;
  sentToPlayerId = original.sentToPlayerId;
  reserved1 = original.reserved1;
  reserved2 = original.reserved2;

  return *this;
}

quint8 AddressHeader::getSenderPlayerId() const {
  return sentFromPlayerId;
}

quint8 AddressHeader::getReceiverPlayerId() const {
  return sentToPlayerId;
}

const quint8 AddressHeader::NO_PLAYER_ID(0xff);
const quint8 AddressHeader::SERVER_PLAYER_ID(0xfe);

ostream& operator<<(ostream& stream, const AddressHeader& addressHeader) {
  stream << "AddressHeader { "
	 << "version=" << addressHeader.version << ", "
	 << "sentFromPlayerId=" << static_cast<unsigned int>(addressHeader.sentFromPlayerId) << ", "
	 << "sentToPlayerId=" << static_cast<unsigned int>(addressHeader.sentToPlayerId) << " }";
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const AddressHeader& addressHeader) {
  stream << addressHeader.version
	 << addressHeader.sentFromPlayerId << addressHeader.sentToPlayerId
	 << addressHeader.reserved1 << addressHeader.reserved2;
  return stream;
}

QDataStream& operator>>(QDataStream& stream, AddressHeader& addressHeader) {
  stream >> addressHeader.version
	 >> addressHeader.sentFromPlayerId >> addressHeader.sentToPlayerId
	 >> addressHeader.reserved1 >> addressHeader.reserved2;
  assert(VERSION_NUMBER == addressHeader.version &&
	 "Message received which is not supported. Please update your program!");
  return stream;
}
