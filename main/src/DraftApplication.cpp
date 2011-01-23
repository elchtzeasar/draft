#include "DraftApplication.h"

#include "AddressedMessage.h"
#include "ConfigurationComponent.h"
#include "NetworkComponent.h"
#include "PlayerId.h"
#include "StateMachineComponent.h"

#include <QObject>

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
  qRegisterMetaType<AddressedMessage>("AddressedMessage");
  qRegisterMetaType<PlayerId>("PlayerId");

  // UI -> NetworkComponent:
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   networkComponent, SLOT(handleHostDraft(unsigned int)) );
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   networkComponent, SLOT(handleConnectToDraft(const QString&, unsigned int)) );

  // UI -> ConfigurationComponent:
  connect( &ui, SIGNAL(setPlayerName(const PlayerId&, QString)),
	   configurationComponent, SLOT(setPlayerName(const PlayerId&, QString)) );
  connect( &ui, SIGNAL(configurationRequest(const PlayerId&)),
	   configurationComponent, SLOT(configurationRequest(const PlayerId&)) );
  connect( &ui, SIGNAL(exit(int)),
	   configurationComponent, SLOT(handleExit(int)) );
  // UI <- ConfigurationComponent:
  connect( configurationComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)),
	   &ui, SLOT(configurationResponse(const PlayerId&, const QString)) );

  // UI -> DraftApplication:
  connect( &ui, SIGNAL(exit(int)),
	   this, SLOT(exit(int)) );

  // UI -> StateMachine:
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   stateMachineComponent, SIGNAL(connectToDraft(const QString&, unsigned int)) );
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   stateMachineComponent, SIGNAL(hostDraft(unsigned int)) );

  // StateMachine -> ConfigurationComponent
  connect( stateMachineComponent, SIGNAL(configurationRequest(const PlayerId&)),
	   configurationComponent, SLOT(configurationRequest(const PlayerId&)) );
  connect( stateMachineComponent, SIGNAL(setOwnPlayerId(const PlayerId&)),
	   configurationComponent, SLOT(setOwnPlayerId(const PlayerId&)) );

  // StateMachine -> NetworkComponent
  connect( stateMachineComponent, SIGNAL(sendData(const AddressedMessage&)),
	   networkComponent, SIGNAL(sendData(const AddressedMessage&)) );

  // ConfigurationComponent -> StateMachine
  connect( configurationComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)),
	   stateMachineComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)) );

  // NetworkComponent -> StateMachine
  connect( networkComponent, SIGNAL(connectedToDraft()),
	   stateMachineComponent, SIGNAL(connectedToDraft()) );
  connect( networkComponent, SIGNAL(clientConnected(const PlayerId&)),
	   stateMachineComponent, SIGNAL(clientConnected(const PlayerId&)) );
  connect( networkComponent, SIGNAL(dataReceived(const AddressedMessage&)),
	   stateMachineComponent, SIGNAL(dataReceived(const AddressedMessage&)) );
}

void DraftApplication::start() {
  stateMachineComponent->start();
}
