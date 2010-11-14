#include "MainWindow.h"

#include "FileMenu.h"
#include "HostDraftDialog.h"

#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>

MainWindow::MainWindow() :
  fileMenu(new FileMenu(this)),
  hostDraftDialog(new HostDraftDialog),
  scrollArea(new QScrollArea)
{
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

    emit hostDraftSignal(portNumber.toUInt());
  }
}

void MainWindow::quitApplication() {
  QApplication::quit();
}
