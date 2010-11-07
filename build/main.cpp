#include "MainWindow.h"
#include "RemoteController.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  MainWindow mainWindow;
  mainWindow.show();

  RemoteController remoteController;
  remoteController.start(QThread::LowPriority);

  return app.exec();
}
