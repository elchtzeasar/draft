#ifndef REMOTE_CONTROLLER_H_
#define REMOTE_CONTROLLER_H_

#include <QString>
#include <QThread>

#include <iostream>

class RemoteController : public QThread {
  Q_OBJECT

 public:
  RemoteController(std::ostream& outputStream, std::istream& inputStream);
  ~RemoteController();

  void run();

 signals:
  void exit(int status);
  void hostDraft(unsigned int port);
  void connectToDraft(const QString& hostName, unsigned int port);
  void setPlayerName(QString playerName);
  void configurationRequest();

 public slots:
  void configurationResponse(const QString playerName);
  
 private:
  void sendHostDraft();
  void connectToDraft();
  void exitCommand();
  void setPlayerName();
  void getPlayerName();

  RemoteController(const RemoteController&);
  RemoteController& operator=(RemoteController&);

  std::ostream& outputStream;
  std::istream& inputStream;
};

#endif // REMOTE_CONTROLLER_H_
