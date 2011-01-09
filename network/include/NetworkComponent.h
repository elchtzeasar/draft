#ifndef NETWORK_COMPONENT_H_
#define NETWORK_COMPONENT_H_

#include <QObject>

class Connection;
class ConnectionListener;
class NetworkComponentFactory;

class AddressedMessage;

class NetworkComponent : public QObject {
  Q_OBJECT

 public:
  NetworkComponent(NetworkComponentFactory& componentFactory,
		   ConnectionListener* connectionListener);
  virtual ~NetworkComponent();

 public slots:
  void handleHostDraft(unsigned int port);
  void handleConnectToDraft(const QString& hostName, unsigned int port);

 signals:
  void connectedToDraft();
  void clientConnected();

  void sendData(const AddressedMessage& message);
  void dataReceived(const AddressedMessage& message);

 private:
  NetworkComponent(const NetworkComponent&);
  NetworkComponent& operator=(NetworkComponent&);

  NetworkComponentFactory& componentFactory;
  ConnectionListener* connectionListener;
};

#endif // NETWORK_COMPONENT_H_
