#include "DraftApplication.h"

#include <QApplication>
#include <QThread>

int main(int argc, char *argv[])
{
  QCoreApplication app(argc, argv);
  // Todo: Make sure the following is used for the gui binary:
  //QApplication app(argc, argv);

  DraftApplication<UI_TYPE> draftAppl;
  draftAppl.connect();

  return app.exec();
}
