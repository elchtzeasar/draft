#include "FileMenu.h"

#include <QAction>
#include <QApplication>

FileMenu::FileMenu(QWidget* parent) :
  QMenu(tr("&File"), parent),
  hostDraftAction(new QAction(tr("&Host draft"), this)),
  quitAction(new QAction(tr("&Quit"), this))
{
  addAction(hostDraftAction);
  addAction(quitAction);

  hostDraftAction->setShortcut(tr("Ctrl+H"));
  quitAction->setShortcut(tr("Ctrl+W"));

  connect(quitAction, SIGNAL(triggered()), this, SLOT(quitApplication()));
  connect(hostDraftAction, SIGNAL(triggered()), parent, SLOT(openHostWindow()));
}

FileMenu::~FileMenu() {
  delete hostDraftAction;
  delete quitAction;
}

void FileMenu::quitApplication() {
  QApplication::quit();
}
