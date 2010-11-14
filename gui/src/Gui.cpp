#include "Gui.h"

#include "MainWindow.h"

Gui::Gui() : mainWindow(new MainWindow) {
  connect(mainWindow, SIGNAL(hostDraftSignal(unsigned int)),
	  this, SIGNAL(hostDraftSignal(unsigned int)));

  mainWindow->show();
}

Gui::~Gui() {
  delete mainWindow;
}

