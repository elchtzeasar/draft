#ifndef CONNECT_TO_DRAFT_DIALOG_H_
#define CONNECT_TO_DRAFT_DIALOG_H_

#include <QDialog>

class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class ConnectToDraftDialog : public QDialog {
  Q_OBJECT

 public:
  ConnectToDraftDialog(QWidget* parent = 0);
  virtual ~ConnectToDraftDialog();

  unsigned int getPortNumber();
  const QString& getHostName();

 private slots:
  void connectClicked();

 private:
  ConnectToDraftDialog(const ConnectToDraftDialog&);
  ConnectToDraftDialog& operator=(ConnectToDraftDialog&);

  unsigned int portNumber;
  QString hostName;

  QHBoxLayout *layout;
  QLabel* hostLabel;
  QLineEdit* hostField;
  QLabel* portLabel;
  QLineEdit* portField;
  QPushButton* hostButton;
};

#endif // CONNECT_TO_DRAFT_DIALOG_H_
