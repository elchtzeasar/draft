#include "Gui.h"
#include "RemoteController.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  Gui gui;

  RemoteController remoteController;
  remoteController.start(QThread::LowPriority);

  return app.exec();
}
