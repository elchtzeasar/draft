#ifndef GUI_H_
#define GUI_H_

#include <QObject>

class MainWindow;

class Gui : public QObject {
  Q_OBJECT

 public:
  Gui();
  ~Gui();

 signals:
  void hostDraftSignal(unsigned int port);
  void connectToDraftSignal(unsigned int port);

 private:
  Gui(const Gui&);
  Gui& operator=(Gui&);

  MainWindow* mainWindow;
};
#endif // GUI_H_
