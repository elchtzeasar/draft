#include "ClientConfiguringState.h"

#include "SendingNameState.h"

ClientConfiguringState::ClientConfiguringState(QObject* component, State* parent, const char* name) :
  State(component, parent, name, false),
  requestingName(new State(component, this, "RequestingName")),
  sendingName(new SendingNameState(component, this)),
  receivingPlayerList(new State(receivingPlayerList, this, "ReceivingPlayerList")) {

  connect(requestingName, SIGNAL(entered()), component, SIGNAL(configurationRequest()));

  requestingName->addTransition(
    component, SIGNAL(configurationResponse(const QString)), sendingName);

  sendingName->addTransition(
    component, SIGNAL(dataReceived(const QByteArray&)), receivingPlayerList);
  connect(sendingName, SIGNAL(sendData(const QByteArray&)),
	  component, SIGNAL(sendData(const QByteArray&)) );

  setInitialState(requestingName);
}

ClientConfiguringState::~ClientConfiguringState() {
  delete sendingName;
  delete requestingName;
}
