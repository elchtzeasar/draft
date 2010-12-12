#include "NetworkComponentFactory.h"

#include "NetworkComponent.h"
#include "ConnectionImpl.h"
#include "ConnectionListenerImpl.h"

#include <QObject>

class QByteArray;

NetworkComponent* NetworkComponentFactory::createComponent() {
  Connection* connection = new ConnectionImpl;
  ConnectionListener* connectionListener = new ConnectionListenerImpl(*connection);
  NetworkComponent* networkComponent =
    new NetworkComponent(connection, connectionListener);

  // NetworkComponent -> Connection
  QObject::connect( networkComponent, SIGNAL(sendData(const QString&)),
		    connection, SLOT(handleSendData(const QString&)) );

  // Connection -> NetworkComponent
  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );
  QObject::connect( connection, SIGNAL(dataReceived(const QString&)),
		    networkComponent, SIGNAL(dataReceived(const QString&)) );

  // ConnectionListener -> NetworkComponent
  QObject::connect( connectionListener, SIGNAL(clientConnected()),
		    networkComponent, SIGNAL(clientConnected()) );

  return networkComponent;
}
