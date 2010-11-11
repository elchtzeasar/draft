#include "Gui.h"

#include "MainWindow.h"

Gui::Gui() : mainWindow(new MainWindow) {
  mainWindow->show();
}

Gui::~Gui() {
  delete mainWindow;
}

