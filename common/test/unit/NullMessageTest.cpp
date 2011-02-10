#include "NullMessage.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

using std::stringstream;
class NullMessageTest : public testing::Test {
};

TEST_F(NullMessageTest, shouldPrintMessageCorrectly) {
  stringstream s;
  NullMessage nullMessage(MessageNumber::NULL_MESSAGE);
  s << nullMessage;

  ASSERT_EQ("NullMessage { NullMessage }", s.str());
}

TEST_F(NullMessageTest, shouldGetACopyOfNullMessageAfterSerializingThenDeserializing) {
  NullMessage nullMessage1(MessageNumber::NULL_MESSAGE), nullMessage2(MessageNumber::NULL_MESSAGE);

  Message& message1(nullMessage1);
  Message& message2(nullMessage2);
  QByteArray byteArray;
  QDataStream writeStream(&byteArray, QIODevice::WriteOnly);
  QDataStream readStream(&byteArray, QIODevice::ReadOnly);

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(nullMessage1, nullMessage2);
}
