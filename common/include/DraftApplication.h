#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include <QCoreApplication>
#include <Qt>
#include <QObject>

class DraftApplication : public QObject {
  Q_OBJECT

 public:
  DraftApplication(QCoreApplication& application,
		   QObject& ui,
		   QObject& configurationComponent,
		   QObject& networkComponent,
		   QObject& stateMachineComponent);

  virtual ~DraftApplication();
  void connectSlotsToSignals();

  public slots:
  void handleExit(int);
 protected:

  QCoreApplication& application;
  QObject& ui;
  QObject& configurationComponent;
  QObject& networkComponent;
  QObject& stateMachineComponent;
};


#endif // DRAFT_APPLICATION_H_
