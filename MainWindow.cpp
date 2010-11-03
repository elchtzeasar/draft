#include "MainWindow.h"

#include "FileMenu.h"

#include <QMenuBar>
#include <QScrollArea>

MainWindow::MainWindow() :
  fileMenu(new FileMenu(this)),
  scrollArea(new QScrollArea)
{
  //scrollArea->setBackgroundRole(QPalette::Dark);
  //scrollArea->setWidget(imageLabel);

  setCentralWidget(scrollArea);

  menuBar()->addMenu(fileMenu);
}

MainWindow::~MainWindow() {
  delete fileMenu;
  delete scrollArea;
}
