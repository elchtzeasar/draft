#ifndef STATE_MACHINE_COMPONENT_WRAPPER_H_
#define STATE_MACHINE_COMPONENT_WRAPPER_H_

#include "AddressedMessage.h"

#include <QObject>
#include <QString>

#include <string>
#include <vector>

class StateMachineComponent;
class PlayerId;

class MessageRouter;

class StateMachineComponentWrapper : public QObject {
  Q_OBJECT
 public:
  StateMachineComponentWrapper(const PlayerId& playerId, StateMachineComponent& component, const MessageRouter& router);
  virtual ~StateMachineComponentWrapper();

  void startComponent();
  void sendHostDraft();
  void sendConnectToDraft();
  void sendConnectedToDraft();
  void sendDataReceived(const AddressedMessage& message);
  void sendConfigurationResponse(const PlayerId& playerId, const QString playerName);
  void sendClientConnected(const PlayerId& playerId);

  bool waitForStateChange();
  bool waitForSendData(const AddressedMessage& message);

  std::string getPlayerName() const;

 signals:
  void hostDraft(unsigned int);

  void connectToDraft(const QString&, unsigned int);
  void connectedToDraft();
  void configurationResponse(const PlayerId&, const QString);

  void dataReceived(const AddressedMessage&);

  void configurationRequest(const PlayerId& playerId);
  void clientConnected(const PlayerId& playerId);

 private slots:
  void handleConfigurationRequest(const PlayerId& playerId);
  void handleSendData(const AddressedMessage&);
  void handleSetOwnPlayerId(const PlayerId& playerId);
  void handleStateChanged();

 private:
  StateMachineComponentWrapper(const StateMachineComponentWrapper&);
  StateMachineComponentWrapper& operator=(const StateMachineComponentWrapper&);

  const PlayerId& playerId;
  StateMachineComponent& component;
  const MessageRouter& router;

  bool stateChanged;
  bool messageReceived;
  std::vector<AddressedMessage> messages;
};

#endif
