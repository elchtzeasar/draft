#include "NetworkComponent.h"

#include "AddressedMessage.h"
#include "AddressHeader.h"
#include "Connection.h"
#include "ConnectionListener.h"
#include "NetworkComponentFactory.h"
#include "PlayerId.h"

#include <QTcpSocket>
#include <cassert>

using std::map;

NetworkComponent::NetworkComponent(NetworkComponentFactory& componentFactory)
  : componentFactory(componentFactory),
    connectionListener(NULL),
    connections() {}

NetworkComponent::~NetworkComponent() {
  delete connectionListener;

  //for (ConnectionMap::iterator it = connections.begin(); it != connections.end(); ++it)
	//delete it->second;
}

void NetworkComponent::addConnection(const PlayerId& playerId, Connection* connection) {
  ConnectionMap::const_iterator it = connections.find(playerId);
  assert(it == connections.end() && "There is already a connection for the playerId given!");

  connections[playerId] = connection;
}

void NetworkComponent::handleHostDraft(unsigned int port) {
  connectionListener = componentFactory.createConnectionListener();
  connectionListener->listen(port);
}

void NetworkComponent::handleConnectToDraft(const QString& hostName, unsigned int port) {
  ConnectionMap::const_iterator it = connections.find(PlayerId::SERVER);
  assert(it == connections.end() && "There is already a connection for the playerId given!");

  connections[PlayerId::SERVER] = componentFactory.createConnection(new QTcpSocket(this));
  connections[PlayerId::SERVER]->connectToHost(hostName, port);
}

void NetworkComponent::handleSendData(const AddressedMessage& message) {
  const PlayerId& playerId(message.getHeader().getReceiverPlayerId());
  ConnectionMap::const_iterator it = connections.find(playerId);
  assert(it != connections.end() && "A connection must be added before data can be received!");

  connections[playerId]->sendData(message);
}
