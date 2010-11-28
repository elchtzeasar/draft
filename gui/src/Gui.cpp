#include "Gui.h"

#include "MainWindow.h"

Gui::Gui() : mainWindow(new MainWindow) {
  connect(mainWindow, SIGNAL(hostDraft(unsigned int)),
	  this, SIGNAL(hostDraft(unsigned int)));
  connect(mainWindow, SIGNAL(connectToDraft(const QString&, unsigned int)),
	  this, SIGNAL(connectToDraft(const QString&, unsigned int)));

  mainWindow->show();
}

Gui::~Gui() {
  delete mainWindow;
}

