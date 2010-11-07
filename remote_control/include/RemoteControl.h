#ifndef REMOTE_CONTROL_H_
#define REMOTE_CONTROL_H_

class RemoteControl {
 public:
  RemoteControl();
  void run();

 private:
  RemoteControl(const RemoteControl&);
  RemoteControl& operator=(RemoteControl&);
};

#endif // REMOTE_CONTROL_H_
