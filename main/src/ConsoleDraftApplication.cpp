#include "ConsoleDraftApplication.h"

ConsoleDraftApplication::ConsoleDraftApplication(int argc, char* argv[]) :
  QCoreApplication(argc, argv),
  DraftApplication(remoteController),
  remoteController(std::cout, std::cin) {
}

int ConsoleDraftApplication::exec() {
  return QCoreApplication::exec();
}

void ConsoleDraftApplication::exit(int status) {
  QCoreApplication::exit(status);
}

void ConsoleDraftApplication::start() {
  DraftApplication::start();

  remoteController.start(QThread::LowPriority);
}
