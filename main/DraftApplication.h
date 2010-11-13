#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "Gui.h"
#include "RemoteController.h"
#include "NetworkComponent.h"

#include <QObject>

#include <iostream>

using std::cin;
using std::cout;

template <class UI>
class DraftApplication {
 public:
  DraftApplication();
  void connect();

 private:
  UI ui;
  NetworkComponent networkComponent;
};

template <class UI>
void DraftApplication<UI>::connect() {
  QObject::connect( &ui, SIGNAL(hostDraftSignal(unsigned int)),
		    &networkComponent, SLOT(hostDraftSlot(unsigned int)) );
  QObject::connect( &ui, SIGNAL(connectToDraftSignal(unsigned int)),
		    &networkComponent, SLOT(connectToDraftSlot(unsigned int)) );
}

template <>
DraftApplication<Gui>::DraftApplication() {
}

template <>
DraftApplication<RemoteController>::DraftApplication()
  : ui(std::cout, std::cin){
  ui.start(QThread::LowPriority);
}

#endif // DRAFT_APPLICATION_H_
