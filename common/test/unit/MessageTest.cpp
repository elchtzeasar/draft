#include "Message.h"
#include "NullMessage.h"

#include <QByteArray>
#include <QDataStream>

#include <sstream>
#include <cstring>

#include <gtest/gtest.h>

using std::stringstream;
class MessageTest : public testing::Test {
protected:
  MessageTest() : 
    byteArray(),
    writeStream(&byteArray, QIODevice::WriteOnly),
    readStream(&byteArray, QIODevice::ReadOnly) {}

  QByteArray byteArray;
  QDataStream writeStream;
  QDataStream readStream;
};

TEST_F(MessageTest, shouldPrintMessageCorrectly) {
  stringstream s;
  NullMessage nullMessage(MessageNumber::NULL_MESSAGE);
  Message& message(nullMessage);
  s << message;

  ASSERT_EQ("Message { messageNumber=NullMessage => NullMessage { NullMessage } }", s.str());
}

TEST_F(MessageTest, shouldGetACopyOfMessageAfterSerializingThenDeserializingWithReferences) {
  NullMessage nullMessage1(MessageNumber::NULL_MESSAGE), nullMessage2(MessageNumber::NULL_MESSAGE);

  Message& message1(nullMessage1);
  Message& message2(nullMessage2);

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(nullMessage1, nullMessage2);
}

TEST_F(MessageTest, shouldGetACopyOfMessageAfterSerializingThenDeserializingWithPointers) {
  NullMessage nullMessage1(MessageNumber::NULL_MESSAGE);

  Message& message1(nullMessage1);
  Message* message2;

  writeStream << message1;
  readStream >> message2;

  ASSERT_EQ(nullMessage1, *message2);
}
