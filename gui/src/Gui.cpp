#include "Gui.h"

#include "MainWindow.h"

Gui::Gui() : mainWindow(new MainWindow) {
  connect(mainWindow, SIGNAL(hostDraftSignal(unsigned int)),
	  this, SIGNAL(hostDraftSignal(unsigned int)));
  connect(mainWindow, SIGNAL(connectToDraftSignal(const QString&, unsigned int)),
	  this, SIGNAL(connectToDraftSignal(const QString&, unsigned int)));

  mainWindow->show();
}

Gui::~Gui() {
  delete mainWindow;
}

