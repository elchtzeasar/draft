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

  QObject::connect( connection, SIGNAL(connectedToDraft()),
		    networkComponent, SIGNAL(connectedToDraft()) );

  return networkComponent;
}
