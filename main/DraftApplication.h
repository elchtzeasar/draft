#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "Gui.h"
#include "RemoteController.h"
#include "ConfigurationComponent.h"
#include "ConfigurationComponentFactory.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactory.h"

#include <QCoreApplication>
#include <QObject>
#include <QString>
#include <QMetaType>

#include <iostream>

using std::cin;
using std::cout;

  // Todo: Make sure the following is used for the gui binary:
  //: public QApplication 

template <class UI>
class DraftApplication : public QCoreApplication {
 public:
  DraftApplication(int argc, char* argv[]);
  ~DraftApplication();
  void createComponents();
  void connectSlotsToSignals();
  int exec();

 private:
  void connect ( const QObject * sender,
		 const char * signal,
		 const QObject * receiver,
		 const char * method,
		 Qt::ConnectionType type = Qt::AutoConnection );

  UI ui;
  ConfigurationComponentFactory configurationComponentFactory;
  ConfigurationComponent* configurationComponent;
  NetworkComponentFactory networkComponentFactory;
  NetworkComponent* networkComponent;
};

template <>
DraftApplication<Gui>::DraftApplication(int argc, char* argv[])
  : QCoreApplication(argc, argv) {
  createComponents();
}

template <>
DraftApplication<RemoteController>::DraftApplication(int argc, char* argv[])
: QCoreApplication(argc, argv), ui(std::cout, std::cin) {
  createComponents();
}

template <class UI>
DraftApplication<UI>::~DraftApplication() {
  delete networkComponent;
}

template <class UI>
void DraftApplication<UI>::connect (const QObject * sender,
				    const char * signal,
				    const QObject * receiver,
				    const char * method,
				    Qt::ConnectionType type) {
  if (!QObject::connect(sender, signal, receiver, method, type)) {
    std::cerr << "Failed to connect signal " << signal << " to slot " << method << '!' << std::endl;
  }
}

template <class UI>
void DraftApplication<UI>::connectSlotsToSignals() {
  connect( &ui, SIGNAL(hostDraft(unsigned int)),
	   networkComponent, SLOT(handleHostDraft(unsigned int)) );
  connect( &ui, SIGNAL(connectToDraft(const QString&, unsigned int)),
	   networkComponent, SLOT(handleConnectToDraft(const QString&, unsigned int)) );
  connect( &ui, SIGNAL(setPlayerName(QString)),
	   configurationComponent, SLOT(setPlayerName(QString)) );
  connect( &ui, SIGNAL(configurationRequest()),
	   configurationComponent, SLOT(configurationRequest()) );
  connect( configurationComponent, SIGNAL(configurationResponse(const QString)),
	   &ui, SLOT(configurationResponse(const QString)) );
}

template <class UI>
void DraftApplication<UI>::createComponents() {
  configurationComponent = configurationComponentFactory.createComponent();
  networkComponent = networkComponentFactory.createComponent();
}

template <>
int DraftApplication<Gui>::exec() {
  return QCoreApplication::exec();
}

template <>
int DraftApplication<RemoteController>::exec() {
  ui.start(QThread::LowPriority);

  return QCoreApplication::exec();
}
#endif // DRAFT_APPLICATION_H_
