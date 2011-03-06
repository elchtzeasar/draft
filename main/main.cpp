#include "DraftApplication.h"

#include "ConfigurationComponent.h"
#include "ConfigurationComponentFactory.h"
#include "NetworkComponent.h"
#include "NetworkComponentFactoryImpl.h"
#include "RemoteController.h"
#include "StateMachineComponent.h"

#include <QCoreApplication>
#include <QThread>

#include <glog/logging.h>
#include <iostream>

int main(int argc, char *argv[])
{
  ConfigurationComponentFactory configurationComponentFactory;
  NetworkComponentFactoryImpl networkComponentFactory;

  ConfigurationComponent* configurationComponent(
    configurationComponentFactory.createComponent());
  NetworkComponent* networkComponent(
    networkComponentFactory.createComponent());

  QCoreApplication qtAppl(argc, argv);

  // TODO: Move into factory:
  StateMachineComponent* stateMachineComponent = new StateMachineComponent;
  stateMachineComponent->start();

  // TODO: Move into factory:
  RemoteController remoteController;
  remoteController.start(QThread::LowPriority);

  // Todo: Make sure a GuiDraftApplication is created for the gui binary
  DraftApplication draftAppl(qtAppl,
			     remoteController,
			     *configurationComponent,
			     *networkComponent,
			     *stateMachineComponent);
  draftAppl.connectSlotsToSignals();

  google::InitGoogleLogging(argv[0]);

  return qtAppl.exec();
}
