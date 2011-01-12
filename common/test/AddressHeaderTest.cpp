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

bool operator==(const AddressHeader& lhs, const AddressHeader& rhs) {
  return memcmp(&lhs, &rhs, sizeof(AddressHeader)) == 0;
}

TEST_F(AddressHeaderTest, shouldPrintHeaderCorrectly) {
  stringstream s;
  AddressHeader addressHeader;
  s << addressHeader;

  ASSERT_EQ("AddressHeader { version=1 }", s.str());
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
