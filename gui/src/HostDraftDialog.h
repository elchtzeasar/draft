#ifndef HOST_DRAFT_DIALOG_H_
#define HOST_DRAFT_DIALOG_H_

#include <QDialog>

class QHBoxLayout;
class QLabel;
class QLineEdit;
class QPushButton;

class HostDraftDialog : public QDialog {
  Q_OBJECT

 public:
  HostDraftDialog(QWidget* parent = 0);
  virtual ~HostDraftDialog();

  unsigned int getPortNumber();

 private slots:
  void hostClicked();

 private:
  HostDraftDialog(const HostDraftDialog&);
  HostDraftDialog& operator=(HostDraftDialog&);

  unsigned int portNumber;

  QHBoxLayout *layout;
  QLabel* portLabel;
  QLineEdit* portField;
  QPushButton* hostButton;
};

#endif // HOST_DRAFT_DIALOG_H_
