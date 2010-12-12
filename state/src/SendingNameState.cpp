#include "SendingNameState.h"

SendingNameState::SendingNameState(QObject* component, State* parent) : 
  State(component, parent, "SendingName") {
}

SendingNameState::~SendingNameState() {}

void SendingNameState::onEntry(QEvent* event) {
  QByteArray data;
  QDataStream out(&data, QIODevice::WriteOnly);
  out.setVersion(QDataStream::Qt_4_0);

  out << "This is server speaking...";

  emit sendData(data);
}
