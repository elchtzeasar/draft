#include "StateMachineComponentWrapper.h"

#include "AddressedMessage.h"
#include "AddressHeader.h"
#include "MessageRouter.h"
#include "NullMessage.h"
#include "PlayerId.h"
#include "StateMachineComponent.h"

#include <QtTest>

#include <glog/logging.h>

#include <cassert>
#include <sstream>
#include <algorithm>

using std::find;
using std::string;
using std::stringstream;
using std::vector;

StateMachineComponentWrapper::StateMachineComponentWrapper(const PlayerId& playerId,
							   StateMachineComponent& component,
							   const MessageRouter& router)
  : playerId(playerId), component(component), router(router), stateChanged(false),
    messageReceived(false) {

  connect( this, SIGNAL(hostDraft(unsigned int)),
	   &component, SIGNAL(hostDraft(unsigned int)) );
  connect( this, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   &component, SIGNAL(connectToDraft(const QString&, unsigned int)) );
  connect( this, SIGNAL(connectedToDraft()),
	   &component, SIGNAL(connectedToDraft()) );
  connect( this, SIGNAL(configurationResponse(const PlayerId&, const QString)),
	   &component, SIGNAL(configurationResponse(const PlayerId&, const QString)) );
  connect( this, SIGNAL(dataReceived(const AddressedMessage&)),
	   &component, SIGNAL(dataReceived(const AddressedMessage&)) );
  connect( this, SIGNAL(clientConnected(const PlayerId&)),
	   &component, SIGNAL(clientConnected(const PlayerId&)) );

  connect( &component, SIGNAL(configurationRequest(const PlayerId&)),
	   this, SLOT(handleConfigurationRequest(const PlayerId&)) );
  connect( &component, SIGNAL(sendData(const AddressedMessage&)),
	   this, SLOT(handleSendData(const AddressedMessage&)) );
  connect( &component, SIGNAL(setOwnPlayerId(const PlayerId&)),
	   this, SLOT(handleSetOwnPlayerId(const PlayerId&)) );
  connect( &component, SIGNAL(stateChanged()),
	   this, SLOT(handleStateChanged()) );
}

StateMachineComponentWrapper::~StateMachineComponentWrapper() {
  disconnect(this, 0, 0, 0);
  disconnect(&component, 0, 0, 0);
}

void StateMachineComponentWrapper::startComponent() {
  component.start();
}

void StateMachineComponentWrapper::sendHostDraft() {
  emit hostDraft(9999);
}

void StateMachineComponentWrapper::sendConnectToDraft() {
  emit connectToDraft("localhost", 9999);
}

void StateMachineComponentWrapper::sendConnectedToDraft() {
  emit connectedToDraft();
}

void StateMachineComponentWrapper::sendDataReceived(const AddressedMessage& message) {
  emit dataReceived(message);
}

void StateMachineComponentWrapper::sendConfigurationResponse(const PlayerId& playerId, const QString playerName) {
  emit configurationResponse(playerId, playerName);
}


void StateMachineComponentWrapper::sendClientConnected(const PlayerId& playerId) {
  emit clientConnected(playerId);
}

bool StateMachineComponentWrapper::waitForStateChange() {
  static int const MAX_WAIT = 100;

  for (int waits = 0; waits < MAX_WAIT && !stateChanged; ++waits)
    QTest::qWait(1);

  const bool returnValue(stateChanged);
  stateChanged = false;

  return returnValue;
}

bool StateMachineComponentWrapper::waitForSendData(const AddressedMessage& message) {
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

string StateMachineComponentWrapper::getPlayerName() const {
  stringstream playerName;
  playerName << "Player " << playerId;

  return playerName.str();
}

void StateMachineComponentWrapper::handleConfigurationRequest(const PlayerId& playerId) {
  QString playerName(getPlayerName().c_str());
  sendConfigurationResponse(playerId, playerName);
}

void StateMachineComponentWrapper::handleSendData(const AddressedMessage& message) {
  messages.push_back(message);

  messageReceived = true;
  router.send(message);
}

void StateMachineComponentWrapper::handleSetOwnPlayerId(const PlayerId& playerId) {
  assert(playerId == this->playerId && "Trying to set wrong playerId for component!");
}

void StateMachineComponentWrapper::handleStateChanged() {
  stateChanged = true;
}
