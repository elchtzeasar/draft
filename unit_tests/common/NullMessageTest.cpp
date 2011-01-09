#include "NullMessage.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

bool operator==(const NullMessage& lhs, const NullMessage& rhs);

using std::stringstream;
class NullMessageTest : public testing::Test {
};

bool operator==(const NullMessage& lhs, const NullMessage& rhs) {
  return memcmp(&lhs, &rhs, sizeof(NullMessage)) == 0;
}

TEST_F(NullMessageTest, shouldPrintMessageCorrectly) {
  stringstream s;
  NullMessage nullMessage(NULL_MESSAGE);
  s << nullMessage;

  ASSERT_EQ("NullMessage { NullMessage }", s.str());
}

TEST_F(NullMessageTest, shouldGetACopyOfNullMessageAfterSerializingThenDeserializing) {
  NullMessage nullMessage1(NULL_MESSAGE), nullMessage2(NULL_MESSAGE);

  Message& message1(nullMessage1);
  Message& message2(nullMessage2);
  QByteArray byteArray;
  QDataStream writeStream(&byteArray, QIODevice::WriteOnly);
  QDataStream readStream(&byteArray, QIODevice::ReadOnly);

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(nullMessage1, nullMessage2);
}
