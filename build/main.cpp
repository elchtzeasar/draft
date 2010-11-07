#include <QApplication>

#include "MainWindow.h"
#include "RemoteControl.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  RemoteControl remoteControl;
  remoteControl.run();

  return app.exec();
}
