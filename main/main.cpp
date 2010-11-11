#include "DraftApplication.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  DraftApplication<UI_TYPE> draftAppl;
  draftAppl.connect();

  return app.exec();
}
