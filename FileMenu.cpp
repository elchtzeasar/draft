#include "FileMenu.h"

#include <QAction>

#include <QApplication>

FileMenu::FileMenu(QWidget* mainWindow) :
  QMenu(tr("&File"), mainWindow),
  hostDraftAction(new QAction(tr("&Host draft"), this)),
  quitAction(new QAction(tr("&Quit"), this))
{
  addAction(hostDraftAction);
  addSeparator();
  addAction(quitAction);

  hostDraftAction->setShortcut(tr("Ctrl+O"));
  quitAction->setShortcut(tr("Ctrl+W"));

  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitApplication()));
}

FileMenu::~FileMenu() {
  delete hostDraftAction;
  delete quitAction;
}

void FileMenu::quitApplication() {
  QApplication::quit();
}
