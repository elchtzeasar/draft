#ifndef NETWORK_COMPONENT_H_
#define NETWORK_COMPONENT_H_

#include <QObject>

class Connection;
class ConnectionListener;

class NetworkComponent : public QObject {
  Q_OBJECT

 public:
  NetworkComponent();
  ~NetworkComponent();

 public slots:
  void hostDraftSlot(unsigned int port);
  void connectToDraftSlot(unsigned int port);

 private:
  Connection* connection;
  ConnectionListener* connectionListener;
};

#endif // NETWORK_COMPONENT_H_
