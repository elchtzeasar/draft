#ifndef NETWORK_COMPONENT_H_
#define NETWORK_COMPONENT_H_

#include <QObject>

class Connection;
class ConnectionListener;
class NetworkComponentFactory;

class PlayerId;
class AddressedMessage;

class NetworkComponent : public QObject {
  Q_OBJECT

 public:
  NetworkComponent(NetworkComponentFactory& componentFactory,
		   ConnectionListener* connectionListener);
  virtual ~NetworkComponent();

  void addConnection(const Connection& connection);

 public slots:
  void handleHostDraft(unsigned int port);
  void handleConnectToDraft(const QString& hostName, unsigned int port);
  void handleSendData(const AddressedMessage& message);

 signals:
  void connectedToDraft();
  void clientConnected(const PlayerId& playerId);

  void dataReceived(const AddressedMessage& message);

 private:
  NetworkComponent(const NetworkComponent&);
  NetworkComponent& operator=(NetworkComponent&);

  NetworkComponentFactory& componentFactory;
  ConnectionListener* connectionListener;
  const Connection* connection;
};

#endif // NETWORK_COMPONENT_H_
