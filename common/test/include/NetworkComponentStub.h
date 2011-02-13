#ifndef NETWORK_COMPONENT_STUB_H_
#define NETWORK_COMPONENT_STUB_H_

#include "AddressedMessage.h"

#include <QObject>
#include <vector>

class PlayerId;
class AddressedMessage;

class QString;

class NetworkComponentStub : public QObject {
  Q_OBJECT

 public:
  void sendConnectedToDraft();
  void sendClientConnected(const PlayerId& playerId);
  void sendDataReceived(const AddressedMessage& message);
  bool waitForSendData(const AddressedMessage& message);

 public slots:
  void handleHostDraft(unsigned int port);
  void handleConnectToDraft(const QString& hostName, unsigned int port);
  void handleSendData(const AddressedMessage& message);

 signals:
  void connectedToDraft();
  void clientConnected(const PlayerId& playerId);
  void dataReceived(const AddressedMessage& message);

 private:
  bool messageReceived;
  std::vector<AddressedMessage> messages;
};

#endif // NETWORK_COMPONENT_STUB_H_
