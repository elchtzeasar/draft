#ifndef REMOTE_CONTROL_H_
#define REMOTE_CONTROL_H_

#include <QThread>

class RemoteControl : public QThread {
  //  Q_OBJECT

 public:
  RemoteControl();
  ~RemoteControl();

  void run();

 private:
  RemoteControl(const RemoteControl&);
  RemoteControl& operator=(RemoteControl&);
};

#endif // REMOTE_CONTROL_H_
