#include "NetworkComponentFactoryImpl.h"

#include "NetworkComponent.h"
#include "ConnectionImpl.h"
#include "ConnectionListenerImpl.h"

#include <QObject>

NetworkComponentFactoryImpl::NetworkComponentFactoryImpl() : networkComponent(0) {
}

NetworkComponent* NetworkComponentFactoryImpl::createComponent() {
  ConnectionListener* connectionListener = new ConnectionListenerImpl(*this);
  networkComponent = new NetworkComponent(*this, connectionListener);

  // ConnectionListener -> NetworkComponent
  QObject::connect( connectionListener, SIGNAL(clientConnected()),
		    networkComponent, SIGNAL(clientConnected()) );

  return networkComponent;
}

Connection* NetworkComponentFactoryImpl::createConnection(QTcpSocket* tcpSocket) {
  Connection* connection = new ConnectionImpl(tcpSocket);

  // NetworkComponent -> Connection
  QObject::connect( networkComponent, SIGNAL(sendData(const AddressedMessage&)),
		    connection, SLOT(handleSendData(const AddressedMessage&)) );

  // Connection -> NetworkComponent
  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );
  QObject::connect( connection, SIGNAL(dataReceived(const AddressedMessage&)),
		    networkComponent, SIGNAL(dataReceived(const AddressedMessage&)) );

  return connection;
}
