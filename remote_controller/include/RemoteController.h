#ifndef REMOTE_CONTROLLER_H_
#define REMOTE_CONTROLLER_H_

#include <QThread>

class RemoteController : public QThread {
  //  Q_OBJECT

 public:
  RemoteController();
  ~RemoteController();

  void run();

 private:
  RemoteController(const RemoteController&);
  RemoteController& operator=(RemoteController&);
};

#endif // REMOTE_CONTROLLER_H_
