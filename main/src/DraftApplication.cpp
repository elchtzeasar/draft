#include "DraftApplication.h"

#include "AddressedMessage.h"
#include "ConfigurationComponent.h"
#include "NetworkComponent.h"
#include "StateMachineComponent.h"

#include <QObject>
#include <QMetaType>

#include <iostream>

using std::cerr;
using std::endl;
DraftApplication::DraftApplication(QObject& ui) :
  ui(ui),
  configurationComponent(configurationComponentFactory.createComponent()),
  networkComponent(networkComponentFactory.createComponent()),
  stateMachineComponent(new StateMachineComponent) {}

DraftApplication::~DraftApplication() {
  delete configurationComponent;
  delete networkComponent;
  delete stateMachineComponent;
}

void DraftApplication::connect (const QObject * sender,
				const char * signal,
				const QObject * receiver,
				const char * method,
				Qt::ConnectionType type) {
  if (!QObject::connect(sender, signal, receiver, method, type)) {
    cerr << "DraftApplication: Failed to connect signal " << signal << " to slot " << method << '!' << endl;
  }
}

void DraftApplication::connectSlotsToSignals() {
  qRegisterMetaType<AddressedMessage>();

  // UI -> NetworkComponent:
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   networkComponent, SLOT(handleHostDraft(unsigned int)) );
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   networkComponent, SLOT(handleConnectToDraft(const QString&, unsigned int)) );

  // UI -> ConfigurationComponent:
  connect( &ui, SIGNAL(setPlayerName(quint8, QString)),
	   configurationComponent, SLOT(setPlayerName(quint8, QString)) );
  connect( &ui, SIGNAL(configurationRequest(quint8)),
	   configurationComponent, SLOT(configurationRequest(quint8)) );
  connect( &ui, SIGNAL(exit(int)),
	   configurationComponent, SLOT(handleExit(int)) );
  // UI <- ConfigurationComponent:
  connect( configurationComponent, SIGNAL(configurationResponse(quint8, const QString)),
	   &ui, SLOT(configurationResponse(quint8, const QString)) );

  // UI -> DraftApplication:
  connect( &ui, SIGNAL(exit(int)),
	   this, SLOT(exit(int)) );

  // UI -> StateMachine:
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   stateMachineComponent, SIGNAL(connectToDraft(const QString&, unsigned int)) );
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   stateMachineComponent, SIGNAL(hostDraft(unsigned int)) );

  // StateMachine -> ConfigurationComponent
  connect( stateMachineComponent, SIGNAL(configurationRequest(quint8)),
	   configurationComponent, SLOT(configurationRequest(quint8)) );

  // StateMachine -> NetworkComponent
  connect( stateMachineComponent, SIGNAL(sendData(const AddressedMessage&)),
	   networkComponent, SIGNAL(sendData(const AddressedMessage&)) );

  // ConfigurationComponent -> StateMachine
  connect( configurationComponent, SIGNAL(configurationResponse(quint8, const QString)),
	   stateMachineComponent, SIGNAL(configurationResponse(quint8, const QString)) );

  // NetworkComponent -> StateMachine
  connect( networkComponent, SIGNAL(connectedToDraft()),
	   stateMachineComponent, SIGNAL(connectedToDraft()) );
  connect( networkComponent, SIGNAL(clientConnected(quint8)),
	   stateMachineComponent, SIGNAL(clientConnected(quint8)) );
  connect( networkComponent, SIGNAL(dataReceived(const AddressedMessage&)),
	   stateMachineComponent, SIGNAL(dataReceived(const AddressedMessage&)) );
}

void DraftApplication::start() {
  stateMachineComponent->start();
}
