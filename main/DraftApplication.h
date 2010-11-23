#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "Gui.h"
#include "RemoteController.h"
#include "ConfigurationComponent.h"
#include "ConfigurationComponentFactory.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactory.h"

#include <QObject>
#include <QString>
#include <QMetaType>

#include <iostream>

using std::cin;
using std::cout;

template <class UI>
class DraftApplication {
 public:
  DraftApplication();
  ~DraftApplication();
  void connect();
  void createComponents();

 private:
  UI ui;
  ConfigurationComponentFactory configurationComponentFactory;
  ConfigurationComponent* configurationComponent;
  NetworkComponentFactory networkComponentFactory;
  NetworkComponent* networkComponent;
};

template <>
DraftApplication<Gui>::DraftApplication() {
  createComponents();
}

template <>
DraftApplication<RemoteController>::DraftApplication()
  : ui(std::cout, std::cin){
  ui.start(QThread::LowPriority);
  createComponents();
}

template <class UI>
DraftApplication<UI>::~DraftApplication() {
  delete networkComponent;
}

template <class UI>
void DraftApplication<UI>::connect() {
  QObject::connect( &ui, SIGNAL(hostDraftSignal(unsigned int)),
		    networkComponent, SLOT(hostDraftSlot(unsigned int)) );
  QObject::connect( &ui, SIGNAL(connectToDraftSignal(const QString&, unsigned int)),
		    networkComponent, SLOT(connectToDraftSlot(const QString&, unsigned int)) );

  QObject::connect( &ui, SIGNAL(setPlayerName(QString)),
		    configurationComponent, SLOT(setPlayerName(QString)) );
  QObject::connect( &ui, SIGNAL(configurationRequest()),
		    configurationComponent, SLOT(configurationRequest()) );
  QObject::connect( configurationComponent, SIGNAL(configurationResponse(const QString)),
		    &ui, SLOT(configurationResponse(const QString)) );
}

template <class UI>
void DraftApplication<UI>::createComponents() {
  configurationComponent = configurationComponentFactory.createComponent();
  networkComponent = networkComponentFactory.createComponent();
}

#endif // DRAFT_APPLICATION_H_
