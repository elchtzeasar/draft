#include "HostDraftDialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

HostDraftDialog::HostDraftDialog(QWidget* parent) :
  QDialog(parent),
  layout(new QHBoxLayout),
  portLabel(new QLabel(tr("Port to use:"))),
  portField(new QLineEdit),
  hostButton(new QPushButton(tr("&Host"))) {
  layout->addWidget(portLabel);
  layout->addWidget(portField);
  layout->addWidget(hostButton);

  setLayout(layout);
  setWindowTitle(tr("Enter port"));

  connect(hostButton, SIGNAL(clicked()), this, SLOT(hostClicked()));
}

HostDraftDialog::~HostDraftDialog() {
  delete layout;
  delete portLabel;
  delete portField;
  delete hostButton;
}

const QString& HostDraftDialog::getPortNumber() {
  return portNumber;
}

void HostDraftDialog::hostClicked() {
  QString text = portField->text();

  if (text.isEmpty()) {
    QMessageBox::information(this, tr("Empty Field"),
			     tr("Please enter a port number."));
  } else {
    portNumber = text;
    portField->clear();
    hide();
    accept();
  }
}
