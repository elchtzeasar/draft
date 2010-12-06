#include "DraftApplication.h"
#include "ConsoleDraftApplication.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  // Todo: Make sure a GuiDraftApplication is created for the gui binary
  DraftApplication* draftAppl = new ConsoleDraftApplication(argc, argv);
  draftAppl->connectSlotsToSignals();
  draftAppl->start();

  return draftAppl->exec();
}
