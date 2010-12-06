#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "ConfigurationComponentFactory.h"
#include "NetworkComponentFactory.h"

#include <Qt>
#include <QObject>

class ConfigurationComponent;
class NetworkComponent;
class StateMachineComponent;


class DraftApplication : public QObject {
  Q_OBJECT

 public:
  DraftApplication(QObject& ui);
  virtual ~DraftApplication();
  void connectSlotsToSignals();
  virtual int exec() = 0;

 public slots:
  virtual void exit(int status) = 0;
  virtual void start();

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
  StateMachineComponent* stateMachineComponent;
};


#endif // DRAFT_APPLICATION_H_
