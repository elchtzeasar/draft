#ifndef CONNECTION_SERVER_H_
#define CONNECTION_SERVER_H_

#include <QTcpServer>
#include <QObject>

class Connection;

class ConnectionListener : public QObject {
  Q_OBJECT

 public:
  ConnectionListener(Connection& connection);

  void listen(unsigned int port);

 private slots:
  void acceptConnection();

 private:
  Connection& connection;
  QTcpServer tcpServer;
};

#endif // CONNECTION_SERVER_H_
