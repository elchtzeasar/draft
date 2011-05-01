#include "NetworkComponentFactoryImpl.h"

#include "NetworkComponent.h"
#include "ConnectionImpl.h"
#include "ConnectionListenerImpl.h"

#include <QObject>

NetworkComponentFactoryImpl::NetworkComponentFactoryImpl() : 
  networkComponent(0) {
}

NetworkComponent* NetworkComponentFactoryImpl::createComponent() {
  networkComponent = new NetworkComponent(*this);

  return networkComponent;
}

Connection* NetworkComponentFactoryImpl::createConnection(QTcpSocket* tcpSocket) {
  Connection* connection = new ConnectionImpl(tcpSocket);

  // Connection -> NetworkComponent
  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );
  QObject::connect( connection, SIGNAL(dataReceived(const AddressedMessage&)),
		    networkComponent, SIGNAL(dataReceived(const AddressedMessage&)) );

  return connection;
}

ConnectionListener* NetworkComponentFactoryImpl::createConnectionListener() {
  ConnectionListener* connectionListener = new ConnectionListenerImpl(*networkComponent, *this);

  // ConnectionListener -> NetworkComponent
  QObject::connect( connectionListener, SIGNAL(clientConnected(const PlayerId&)),
		    networkComponent, SIGNAL(clientConnected(const PlayerId&)) );

  return connectionListener;
}
