#ifndef FILE_MENU_H_
#define FILE_MENU_H_

#include <QMenu>

class QAction;
class QWidget;

class FileMenu : public QMenu {
  Q_OBJECT

 public:
  FileMenu(QWidget* mainWindow);
  virtual ~FileMenu();

 private slots:
  void quitApplication();

 private:
  QAction* hostDraftAction;
  QAction* quitAction;

  FileMenu(const FileMenu&);
  FileMenu& operator=(FileMenu&);
};

#endif // FILE_MENU_H_
