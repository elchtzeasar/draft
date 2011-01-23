#include "AddressHeader.h"

#include <QDataStream>

#include <cassert>

using std::ostream;

static quint32 VERSION_NUMBER(1);

AddressHeader::AddressHeader() :
  version(VERSION_NUMBER),
  sentFromPlayerId(PlayerId::NONE),
  sentToPlayerId(PlayerId::NONE),
  reserved1(0),
  reserved2(0) {}

AddressHeader::AddressHeader(const PlayerId& sentFromPlayerId,
			     const PlayerId& sentToPlayerId) :
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

const PlayerId& AddressHeader::getSenderPlayerId() const {
  return sentFromPlayerId;
}

const PlayerId& AddressHeader::getReceiverPlayerId() const {
  return sentToPlayerId;
}

ostream& operator<<(ostream& stream, const AddressHeader& addressHeader) {
  stream << "AddressHeader { "
	 << "version=" << addressHeader.version << ", "
	 << "sentFromPlayerId=" << addressHeader.sentFromPlayerId << ", "
	 << "sentToPlayerId=" << addressHeader.sentToPlayerId << " }";
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
