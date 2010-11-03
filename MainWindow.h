#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

class FileMenu;
class QScrollArea;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  virtual ~MainWindow();

 private:
  MainWindow(const MainWindow&);
  MainWindow& operator=(MainWindow&);

  FileMenu* fileMenu;

  QScrollArea* scrollArea;
};

#endif // MAIN_WINDOW_H_
