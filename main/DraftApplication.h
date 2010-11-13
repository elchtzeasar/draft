#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "Gui.h"
#include "RemoteController.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactory.h"

#include <QObject>

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
  QObject::connect( &ui, SIGNAL(connectToDraftSignal(unsigned int)),
		    networkComponent, SLOT(connectToDraftSlot(unsigned int)) );
}

template <class UI>
void DraftApplication<UI>::createComponents() {
  networkComponent = networkComponentFactory.createComponent();
}

#endif // DRAFT_APPLICATION_H_
