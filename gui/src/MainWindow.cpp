#include "MainWindow.h"

#include "FileMenu.h"
#include "HostDraftDialog.h"
#include "ConnectToDraftDialog.h"

#include <QApplication>
#include <QMenuBar>
#include <QMessageBox>
#include <QScrollArea>

MainWindow::MainWindow() :
  fileMenu(new FileMenu(this)),
  hostDraftDialog(new HostDraftDialog(this)),
  connectToDraftDialog(new ConnectToDraftDialog(this)),
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

void MainWindow::openHostDraftWindow() {
  hostDraftDialog->show();

  if (hostDraftDialog->exec() == QDialog::Accepted) {
    emit hostDraftSignal(hostDraftDialog->getPortNumber());
  }
}

void MainWindow::openConnectToDraftWindow() {
  connectToDraftDialog->show();

  if (connectToDraftDialog->exec() == QDialog::Accepted) {
    emit connectToDraftSignal(connectToDraftDialog->getHostName(),
			      connectToDraftDialog->getPortNumber());
  }
}

void MainWindow::quitApplication() {
  QApplication::quit();
}
