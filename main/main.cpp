#include "DraftApplication.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  DraftApplication<UI_TYPE> draftAppl(argc, argv);
  draftAppl.connectSlotsToSignals();

  return draftAppl.exec();
}
