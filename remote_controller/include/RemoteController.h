#ifndef REMOTE_CONTROLLER_H_
#define REMOTE_CONTROLLER_H_

#include <QString>
#include <QThread>

#include <iostream>

class PlayerId;

class RemoteController : public QThread {
  Q_OBJECT

 public:
  RemoteController();
  ~RemoteController();

  void run();

 signals:
  void exit(int status);
  void hostDraft(unsigned int port);
  void connectToDraft(const QString& hostName, unsigned int port);
  void setPlayerName(const PlayerId& playerId, QString playerName);
  void configurationRequest(const PlayerId& playerId);

 public slots:
  void handleConfigurationResponse(const PlayerId& playerId, const QString playerName);
  void handleConnectedToServer();
  void handlePlayerConnected(const PlayerId& playerId, const QString& playerName);

private:
  void sendHostDraft();
  void connectToDraft();
  void exitCommand();
  void setPlayerName();
  void getPlayerName();

  RemoteController(const RemoteController&);
  RemoteController& operator=(RemoteController&);
};

#endif // REMOTE_CONTROLLER_H_
