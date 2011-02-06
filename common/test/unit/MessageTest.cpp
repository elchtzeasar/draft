#include "Message.h"
#include "NullMessage.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

using std::stringstream;
class MessageTest : public testing::Test {
};

TEST_F(MessageTest, shouldPrintMessageCorrectly) {
  stringstream s;
  NullMessage nullMessage(NULL_MESSAGE);
  Message& message(nullMessage);
  s << message;

  ASSERT_EQ("Message { messageNumber=0 => NullMessage { NullMessage } }", s.str());
}

TEST_F(MessageTest, shouldGetACopyOfMessageAfterSerializingThenDeserializingWithReferences) {
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

TEST_F(MessageTest, shouldGetACopyOfMessageAfterSerializingThenDeserializingWithPointers) {
  NullMessage nullMessage1(NULL_MESSAGE);

  Message& message1(nullMessage1);
  Message* message2;
  QByteArray byteArray;
  QDataStream writeStream(&byteArray, QIODevice::WriteOnly);
  QDataStream readStream(&byteArray, QIODevice::ReadOnly);

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(nullMessage1, *message2);
}
