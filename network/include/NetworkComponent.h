#ifndef NETWORK_COMPONENT_H_
#define NETWORK_COMPONENT_H_

#include <QObject>

class Connection;
class ConnectionListener;

class QString;

class NetworkComponent : public QObject {
  Q_OBJECT

 public:
  NetworkComponent(Connection* connection, ConnectionListener* connectionListner);
  ~NetworkComponent();

 public slots:
  void handleHostDraft(unsigned int port);
  void handleConnectToDraft(const QString& hostName, unsigned int port);

 signals:
  void connectedToDraft();

 private:
  NetworkComponent(const NetworkComponent&);
  NetworkComponent& operator=(NetworkComponent&);

  Connection* connection;
  ConnectionListener* connectionListener;
};

#endif // NETWORK_COMPONENT_H_
