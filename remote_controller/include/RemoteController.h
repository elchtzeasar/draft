#ifndef REMOTE_CONTROLLER_H_
#define REMOTE_CONTROLLER_H_

#include <QThread>

class RemoteController : public QThread {
  Q_OBJECT

 public:
  RemoteController();
  ~RemoteController();

  void run();

 signals:
  void hostDraftSignal(unsigned int port);
  void connectToDraftSignal();

 private:
  RemoteController(const RemoteController&);
  RemoteController& operator=(RemoteController&);
};

#endif // REMOTE_CONTROLLER_H_
