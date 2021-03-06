#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>

class FileMenu;
class HostDraftDialog;
class ConnectToDraftDialog;

class QScrollArea;
class QString;

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  virtual ~MainWindow();

 signals:
  void hostDraft(unsigned int port);
  void connectToDraft(const QString& hostName, unsigned int port);

 public slots:
  void quitApplication();
  void openHostDraftWindow();
  void openConnectToDraftWindow();

 private:
  MainWindow(const MainWindow&);
  MainWindow& operator=(MainWindow&);

  FileMenu* fileMenu;
  HostDraftDialog* hostDraftDialog;
  ConnectToDraftDialog* connectToDraftDialog;

  QScrollArea* scrollArea;
};

#endif // MAIN_WINDOW_H_
