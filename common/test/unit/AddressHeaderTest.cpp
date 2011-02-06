#include "AddressHeader.h"

#include "PlayerId.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

using std::stringstream;
class AddressHeaderTest : public testing::Test {
};

static const PlayerId SENT_FROM_PLAYER(1);
static const PlayerId SENT_TO_PLAYER(3);

TEST_F(AddressHeaderTest, shouldPrintHeaderCorrectly) {
  stringstream serializedStream, expectedString;
  AddressHeader addressHeader(SENT_FROM_PLAYER, SENT_TO_PLAYER);
  serializedStream << addressHeader;

  expectedString << "AddressHeader { version=1, "
		 << "sentFromPlayerId=" << SENT_FROM_PLAYER << ", "
		 << "sentToPlayerId=" << SENT_TO_PLAYER << " }";
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
