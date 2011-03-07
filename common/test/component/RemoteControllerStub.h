#ifndef REMOTE_CONTROLLER_STUB_H_
#define REMOTE_CONTROLLER_STUB_H_

#include <QObject>
#include <QString>

class PlayerId;

class RemoteControllerStub : public QObject {
  Q_OBJECT

 public:
  virtual ~RemoteControllerStub();

  void run();
  
  void sendExit(int status);
  void sendHostDraft(unsigned int port);
  void sendConnectToDraft(const QString& hostName, unsigned int port);
  void sendUpdatePlayerConfiguration(const PlayerId& playerId, QString playerName);
  void sendConfigurationRequest(const PlayerId& playerId);

 public slots:
  void handleConfigurationResponse(const PlayerId& playerId, const QString playerName);
  void handleConnectedToServer();
  void handlePlayerConnected(const PlayerId&, const QString& playerName);

 signals:
  void exit(int status);
  void hostDraft(unsigned int port);
  void connectToDraft(const QString& hostName, unsigned int port);
  void updatePlayerConfiguration(const PlayerId& playerId, QString playerName);
  void configurationRequest(const PlayerId& playerId);
};

#endif // REMOTE_CONTROLLER_STUB_H_
