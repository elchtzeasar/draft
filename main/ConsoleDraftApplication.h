#ifndef CONSOLE_DRAFT_APPLICATION_H_
#define CONSOLE_DRAFT_APPLICATION_H_

#include "DraftApplication.h"
#include "RemoteController.h"

#include <QCoreApplication>

class ConsoleDraftApplication : public QCoreApplication, public DraftApplication {
 public:
  ConsoleDraftApplication(int argc, char* argv[]);
  virtual ~ConsoleDraftApplication() {}
  void createComponents();
  void connectSlotsToSignals();
  virtual int exec();

 public slots:
  virtual void exit(int status);

 private:
  RemoteController remoteController;
};

#endif // CONSOLE_DRAFT_APPLICATION_H_
