#include "NetworkComponentStub.h"

#include "PlayerId.h"
#include "vlog.h"

#include <QString>
#include <QTest>
#include <glog/logging.h>
#include <algorithm>

using std::find;
using std::vector;

NetworkComponentStub::~NetworkComponentStub() {}

void NetworkComponentStub::sendConnectedToDraft() {
  emit connectedToDraft();
}

void NetworkComponentStub::sendClientConnected(const PlayerId& playerId) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendClientConnected(" << playerId << ')';
  emit clientConnected(playerId);
}

void NetworkComponentStub::sendDataReceived(const AddressedMessage& message) {
  VLOG(COMPONENT_STUB_VLEVEL) << "sendDataReceived(" << message << ')';
  emit dataReceived(message);
}

void NetworkComponentStub::handleHostDraft(unsigned int port) {
  LOG(WARNING) << "handleHostDraft(" << port 
	       << ") called, not doing anything...";
}

void NetworkComponentStub::handleConnectToDraft(const QString& hostName, unsigned int port) {
  LOG(WARNING) << "handleConnectToDraftDraft(" << hostName.toStdString()
	       << ", " << port 
	       << ") called, not doing anything...";
}

void NetworkComponentStub::handleSendData(const AddressedMessage& message) {
  VLOG(COMPONENT_STUB_VLEVEL) << "handleSendData(" << message << ')';
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

