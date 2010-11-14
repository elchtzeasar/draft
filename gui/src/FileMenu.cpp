#include "FileMenu.h"

#include <QAction>

FileMenu::FileMenu(QWidget* parent) :
  QMenu(tr("&File"), parent),
  hostDraftAction(new QAction(tr("&Host draft"), this)),
  connectToDraftAction(new QAction(tr("&Join draft"), this)),
  quitAction(new QAction(tr("&Quit"), this))
{
  addAction(hostDraftAction);
  addAction(connectToDraftAction);
  addAction(quitAction);

  hostDraftAction->setShortcut(tr("Ctrl+H"));
  connectToDraftAction->setShortcut(tr("Ctrl+J"));
  quitAction->setShortcut(tr("Ctrl+W"));

  connect(quitAction, SIGNAL(triggered()), parent, SLOT(quitApplication()));
  connect(hostDraftAction, SIGNAL(triggered()), parent, SLOT(openHostDraftWindow()));
  connect(connectToDraftAction, SIGNAL(triggered()), parent, SLOT(openConnectToDraftWindow()));
}

FileMenu::~FileMenu() {
  delete hostDraftAction;
  delete quitAction;
}
