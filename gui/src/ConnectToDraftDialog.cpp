#include "ConnectToDraftDialog.h"

#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QString>

ConnectToDraftDialog::ConnectToDraftDialog(QWidget* parent) :
  QDialog(parent),
  layout(new QHBoxLayout),
  hostLabel(new QLabel(tr("Host to connect to:"))),
  hostField(new QLineEdit),
  portLabel(new QLabel(tr("Port to use:"))),
  portField(new QLineEdit),
  hostButton(new QPushButton(tr("&Join"))) {
  layout->addWidget(hostLabel);
  layout->addWidget(hostField);
  layout->addWidget(portLabel);
  layout->addWidget(portField);
  layout->addWidget(hostButton);

  setLayout(layout);
  setWindowTitle(tr("Connect to host"));

  connect(hostButton, SIGNAL(clicked()), this, SLOT(connectClicked()));
}

ConnectToDraftDialog::~ConnectToDraftDialog() {
  delete layout;
  delete hostLabel;
  delete hostField;
  delete portLabel;
  delete portField;
  delete hostButton;
}

unsigned int ConnectToDraftDialog::getPortNumber() {
  return portNumber;
}

const QString& ConnectToDraftDialog::getHostName() {
  return hostName;
}

void ConnectToDraftDialog::connectClicked() {
  QString hostNameText = hostField->text();
  QString portText = portField->text();
  bool intConversionOk;
  unsigned int tempPort = portText.toUInt(&intConversionOk);

  if (portText.isEmpty()) {
    QMessageBox::information(this, tr("Empty Field"),
			     tr("Please enter a port number."));
    return;
  }

  if (!intConversionOk) {
    portText.append(' ');
    portText.append(tr("is not a number. Please enter a port number."));
    QMessageBox::information(this, tr("Not a number"), portText);
    return;
  }

  portNumber = tempPort;
  hostName = hostNameText;
  portField->clear();
  hide();
  accept();
}
