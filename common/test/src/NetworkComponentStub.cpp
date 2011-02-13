#include "NetworkComponentStub.h"

#include <QTest>
#include <algorithm>

using std::find;
using std::vector;

void NetworkComponentStub::sendConnectedToDraft() {
  emit connectedToDraft();
}

void NetworkComponentStub::sendClientConnected(const PlayerId& playerId) {
  emit clientConnected(playerId);
}

void NetworkComponentStub::sendDataReceived(const AddressedMessage& message) {
  emit dataReceived(message);
}

void NetworkComponentStub::handleHostDraft(unsigned int port) {
}

void NetworkComponentStub::handleConnectToDraft(const QString& hostName, unsigned int port) {
}

void NetworkComponentStub::handleSendData(const AddressedMessage& message) {
  messages.push_back(message);

  messageReceived = true;
}

bool NetworkComponentStub::waitForSendData(const AddressedMessage& message) {
  static int const MAX_WAITS = 100;

  int waits(0);
  bool messageFound(false);
  while (waits < MAX_WAITS && !messageFound) {
    ++waits;
    // Wait until a message has been received
    for (; waits < MAX_WAITS && !messageReceived; ++waits)
      QTest::qWait(1);

    vector<AddressedMessage>::iterator it =
      find(messages.begin(), messages.end(), message);

    messageFound = (it != messages.end());
  }

  messageReceived = false;
  return messageFound;
}

