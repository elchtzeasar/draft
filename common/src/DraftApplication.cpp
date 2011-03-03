#include "DraftApplication.h"

#include "AddressedMessage.h"
#include "PlayerId.h"

#include <QObject>

#include <glog/logging.h>

DraftApplication::DraftApplication(QCoreApplication& application,
				   QObject& ui,
				   QObject& configurationComponent,
				   QObject& networkComponent,
				   QObject& stateMachineComponent) :
  application(application),
  ui(ui),
  configurationComponent(configurationComponent),
  networkComponent(networkComponent),
  stateMachineComponent(stateMachineComponent) {}

DraftApplication::~DraftApplication() {
}

void DraftApplication::handleExit(int exitCode) {
  application.exit(exitCode);
}

void DraftApplication::connectSlotsToSignals() {
  qRegisterMetaType<AddressedMessage>("AddressedMessage");
  qRegisterMetaType<PlayerId>("PlayerId");

  // UI -> StateMachine:
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   &stateMachineComponent, SIGNAL(connectToDraft(const QString&, unsigned int)) );
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   &stateMachineComponent, SIGNAL(hostDraft(unsigned int)) );
  // UI <- StateMachine

  // StateMachine -> NetworkComponent:
  connect( &stateMachineComponent, SIGNAL(hostDraft(unsigned int)),
	   &networkComponent, SLOT(handleHostDraft(unsigned int)) );
  connect( &stateMachineComponent, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   &networkComponent, SLOT(handleConnectToDraft(const QString&, unsigned int)) );
  connect( &stateMachineComponent, SIGNAL(sendData(const AddressedMessage&)),
	   &networkComponent, SLOT(handleSendData(const AddressedMessage&)) );
  // StateMahine <- NetworkComponent
  connect( &networkComponent, SIGNAL(connectedToDraft()),
	   &stateMachineComponent, SIGNAL(connectedToDraft()) );
  connect( &networkComponent, SIGNAL(clientConnected(const PlayerId&)),
	   &stateMachineComponent, SIGNAL(clientConnected(const PlayerId&)) );
  connect( &networkComponent, SIGNAL(dataReceived(const AddressedMessage&)),
	   &stateMachineComponent, SIGNAL(dataReceived(const AddressedMessage&)) );

  
  // StateMachine -> ConfigurationComponent
  connect( &stateMachineComponent, SIGNAL(configurationRequest(const PlayerId&)),
	   &configurationComponent, SLOT(handleConfigurationRequest(const PlayerId&)) );
  connect( &stateMachineComponent, SIGNAL(setOwnPlayerId(const PlayerId&)),
	   &configurationComponent, SLOT(handleSetOwnPlayerId(const PlayerId&)) );

  // StateMachine <- ConfigurationComponent
  connect( &configurationComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)),
	   &stateMachineComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)) );

  // UI -> ConfigurationComponent:
  connect( &ui, SIGNAL(setPlayerName(const PlayerId&, QString)),
	   &configurationComponent, SLOT(handleSetPlayerName(const PlayerId&, QString)) );
  connect( &ui, SIGNAL(configurationRequest(const PlayerId&)),
	   &configurationComponent, SLOT(handleConfigurationRequest(const PlayerId&)) );
  connect( &ui, SIGNAL(exit(int)),
	   &configurationComponent, SLOT(handleExit(int)) );
  // UI <- ConfigurationComponent:
  connect( &configurationComponent, SIGNAL(configurationResponse(const PlayerId&, const QString)),
	   &ui, SLOT(handleConfigurationResponse(const PlayerId&, const QString)) );

  // UI -> DraftApplication:
  connect( &ui, SIGNAL(exit(int)),
	   this, SLOT(handleExit(int)) );
}
