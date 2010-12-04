#include "DraftApplication.h"

#include <QObject>

#include <iostream>

using std::cerr;
using std::endl;
DraftApplication::DraftApplication(QObject& ui) :
  ui(ui),
  configurationComponent(configurationComponentFactory.createComponent()),
  networkComponent(networkComponentFactory.createComponent()) {}

DraftApplication::~DraftApplication() {
  delete configurationComponent;
  delete networkComponent;
}

void DraftApplication::connect (const QObject * sender,
				const char * signal,
				const QObject * receiver,
				const char * method,
				Qt::ConnectionType type) {
  if (!QObject::connect(sender, signal, receiver, method, type)) {
    cerr << "Failed to connect signal " << signal << " to slot " << method << '!' << endl;
  }
}

void DraftApplication::connectSlotsToSignals() {
  // UI -> NetworkComponent:
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   networkComponent, SLOT(handleHostDraft(unsigned int)) );
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   networkComponent, SLOT(handleConnectToDraft(const QString&, unsigned int)) );

  // UI -> ConfigurationComponent:
  connect( &ui, SIGNAL(setPlayerName(QString)),
	   configurationComponent, SLOT(setPlayerName(QString)) );
  connect( &ui, SIGNAL(configurationRequest()),
	   configurationComponent, SLOT(configurationRequest()) );
  // UI <- ConfigurationComponent:
  connect( configurationComponent, SIGNAL(configurationResponse(const QString)),
	   &ui, SLOT(configurationResponse(const QString)) );

  // UI -> DraftApplication:
  connect( &ui, SIGNAL(exit(int)),
	   this, SLOT(exit(int)) );
}
