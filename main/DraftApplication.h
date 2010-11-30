#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "ConfigurationComponent.h"
#include "ConfigurationComponentFactory.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactory.h"

#include <Qt>

class QObject;

class DraftApplication : public QObject {
  Q_OBJECT

 public:
  DraftApplication(QObject& ui);
  virtual ~DraftApplication();
  void connectSlotsToSignals();
  virtual int exec() = 0;

 public slots:
  virtual void exit(int status) = 0;

 protected:
  void connect ( const QObject * sender,
		 const char * signal,
		 const QObject * receiver,
		 const char * method,
		 Qt::ConnectionType type = Qt::AutoConnection );

  QObject& ui;
  ConfigurationComponentFactory configurationComponentFactory;
  ConfigurationComponent* configurationComponent;
  NetworkComponentFactory networkComponentFactory;
  NetworkComponent* networkComponent;
};


#endif // DRAFT_APPLICATION_H_
