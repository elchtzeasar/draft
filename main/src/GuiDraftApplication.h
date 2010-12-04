#ifndef GUI_DRAFT_APPLICATION_H_
#define GUI_DRAFT_APPLICATION_H_

#include "DraftApplication.h"
#include "Gui.h"

#include <QApplication>

class GuiDraftApplication : public QApplication, public DraftApplication {
 public:
  GuiDraftApplication(int argc, char* argv[]);
  virtual ~GuiDraftApplication() {}
  void createComponents();
  void connectSlotsToSignals();
  virtual int exec() = 0;

 public slots:
  virtual void exit(int status);

 private:
  Gui gui;
};

#endif // GUI_DRAFT_APPLICATION_H_
