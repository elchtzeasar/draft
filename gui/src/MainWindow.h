#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

class FileMenu;
class HostDraftDialog;

class QScrollArea;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  virtual ~MainWindow();

 signals:
  void hostDraftSignal(unsigned int port);

 public slots:
  void quitApplication();
  void openHostWindow();

 private:
  MainWindow(const MainWindow&);
  MainWindow& operator=(MainWindow&);

  FileMenu* fileMenu;
  HostDraftDialog* hostDraftDialog;

  QScrollArea* scrollArea;
};

#endif // MAIN_WINDOW_H_
