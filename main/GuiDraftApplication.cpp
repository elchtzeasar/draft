#include "GuiDraftApplication.h"

GuiDraftApplication::GuiDraftApplication(int argc, char* argv[])
  : QApplication(argc, argv), DraftApplication(gui) {
}

int GuiDraftApplication::exec() {
  return QCoreApplication::exec();
}

void GuiDraftApplication::exit(int status) {
  QApplication::exit(status);
}
