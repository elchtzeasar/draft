#include "MainWindow.h"

#include "FileMenu.h"
#include "HostDraftDialog.h"

#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>

MainWindow::MainWindow() :
  fileMenu(new FileMenu(this)),
  hostDraftDialog(new HostDraftDialog),
  scrollArea(new QScrollArea)
{
  //scrollArea->setBackgroundRole(QPalette::Dark);
  //scrollArea->setWidget(imageLabel);

  setCentralWidget(scrollArea);

  menuBar()->addMenu(fileMenu);
}

MainWindow::~MainWindow() {
  delete fileMenu;
  delete hostDraftDialog;
  delete scrollArea;
}

void MainWindow::openHostWindow() {
  hostDraftDialog->show();

  if (hostDraftDialog->exec() == QDialog::Accepted) {
    QString portNumber = hostDraftDialog->getPortNumber();

    if (false/* create socket */) {
      // listen
    } else {
      QMessageBox::information(this, tr("Some error"),
			       tr("Problem with port: \"%1\"?").arg(portNumber));
      return;
    }
  }
}
