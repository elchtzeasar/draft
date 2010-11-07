#include "MainWindow.h"
#include "RemoteControl.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  RemoteControl remoteControl;
  remoteControl.start(QThread::LowPriority);

  return app.exec();
}
