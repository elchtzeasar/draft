#ifndef GUI_H_
#define GUI_H_

#include <QObject>

class MainWindow;
class QString;

class Gui : public QObject {
  Q_OBJECT

 public:
  Gui();
  ~Gui();

 signals:
  void hostDraft(unsigned int port);
  void connectToDraft(const QString& hostName, unsigned int port);

 private:
  Gui(const Gui&);
  Gui& operator=(Gui&);

  MainWindow* mainWindow;
};
#endif // GUI_H_
