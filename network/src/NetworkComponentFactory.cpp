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
  QObject::connect( networkComponent, SIGNAL(sendData(const QByteArray&)),
		    connection, SLOT(handleSendData(const QByteArray&)) );

  // Connection -> NetworkComponent
  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );
  QObject::connect( connection, SIGNAL(dataReceived(const QByteArray&)),
		    networkComponent, SIGNAL(dataReceived(const QByteArray&)) );

  // ConnectionListener -> NetworkComponent
  QObject::connect( connectionListener, SIGNAL(clientConnected()),
		    networkComponent, SIGNAL(clientConnected()) );

  return networkComponent;
}
