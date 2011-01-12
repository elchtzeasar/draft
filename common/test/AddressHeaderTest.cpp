#include "AddressHeader.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

bool operator==(const AddressHeader& lhs, const AddressHeader& rhs);

using std::stringstream;
class AddressHeaderTest : public testing::Test {
};

static const quint8 SENT_FROM_PLAYER(1);
static const quint8 SENT_TO_PLAYER(3);

bool operator==(const AddressHeader& lhs, const AddressHeader& rhs) {
  return memcmp(&lhs, &rhs, sizeof(AddressHeader)) == 0;
}

TEST_F(AddressHeaderTest, shouldPrintHeaderCorrectly) {
  stringstream serializedStream, expectedString;
  AddressHeader addressHeader(SENT_FROM_PLAYER, SENT_TO_PLAYER);
  serializedStream << addressHeader;

  expectedString << "AddressHeader { version=1, "
		 << "sentFromPlayerId=" << static_cast<unsigned int>(SENT_FROM_PLAYER) << ", "
		 << "sentToPlayerId=" << static_cast<unsigned int>(SENT_TO_PLAYER) << " }";
  ASSERT_EQ(expectedString.str().c_str(), serializedStream.str());
}

TEST_F(AddressHeaderTest, shouldGetACopyOfAddressHeaderAfterSerializingThenDeserializing) {
  AddressHeader addressHeader1, addressHeader2;
  QByteArray byteArray;
  QDataStream writeStream(&byteArray, QIODevice::WriteOnly);
  QDataStream readStream(&byteArray, QIODevice::ReadOnly);

  writeStream << addressHeader1;
  readStream >> addressHeader2;

  ASSERT_EQ(addressHeader1, addressHeader2);
}
