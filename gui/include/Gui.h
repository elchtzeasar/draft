#ifndef GUI_H_
#define GUI_H_

#include <QObject>

class MainWindow;

class Gui : public QObject {
  Q_OBJECT
 public:
  Gui();
  ~Gui();

 private:
  Gui(const Gui&);
  Gui& operator=(Gui&);

  MainWindow* mainWindow;
};
#endif // GUI_H_
