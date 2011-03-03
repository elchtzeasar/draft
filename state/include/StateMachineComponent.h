#ifndef STATE_MACHINE_COMPONENT_H_
#define STATE_MACHINE_COMPONENT_H_

#include <QObject>
#include <QState>
#include <QStateMachine>

class State;
class ClientState;
class ServerState;
class AddressedMessage;
class PlayerId;

class StateMachineComponent : public QObject {
  Q_OBJECT

 public:
  StateMachineComponent();
  virtual ~StateMachineComponent();

  void start();

 signals:
  void hostDraft(unsigned int);
  void clientConnected(const PlayerId& playerId);

  void connectToDraft(const QString&, unsigned int);
  void connectedToDraft();
  void configurationRequest(const PlayerId& playerId);
  void configurationResponse(const PlayerId& playerId, const QString);

  void sendData(const AddressedMessage&);
  void dataReceived(const AddressedMessage&);

  void setOwnPlayerId(const PlayerId& playerId);

  void stateChanged(const QString& stateName);

  void connectedToServer();
  void playerConnected(const PlayerId& playerId, const QString& playerName);

 private:
  Q_PROPERTY(QString activeState READ getActiveState WRITE setActiveState);

  const QString getActiveState() const;
  void setActiveState(QString newState);

  QStateMachine* stateMachine;
  State* chooseClientOrServer;
  ClientState* clientState;
  ServerState* serverState;
  QString activeState;
};

#endif // STATE_MACHINE_COMPONENT_H_
