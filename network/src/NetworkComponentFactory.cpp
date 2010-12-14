#include "NetworkComponentFactory.h"

#include "NetworkComponent.h"
#include "ConnectionImpl.h"
#include "ConnectionListenerImpl.h"

#include <QObject>

NetworkComponent* NetworkComponentFactory::createComponent() {
  Connection* connection = new ConnectionImpl;
  ConnectionListener* connectionListener = new ConnectionListenerImpl(*connection);
  NetworkComponent* networkComponent =
    new NetworkComponent(connection, connectionListener);

  // NetworkComponent -> Connection
  QObject::connect( networkComponent, SIGNAL(sendData(const AddressedMessage&)),
		    connection, SLOT(handleSendData(const AddressedMessage&)) );

  // Connection -> NetworkComponent
  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );
  QObject::connect( connection, SIGNAL(dataReceived(const AddressedMessage&)),
		    networkComponent, SIGNAL(dataReceived(const AddressedMessage&)) );

  // ConnectionListener -> NetworkComponent
  QObject::connect( connectionListener, SIGNAL(clientConnected()),
		    networkComponent, SIGNAL(clientConnected()) );

  return networkComponent;
}
