#ifndef DRAFT_APPLICATION_H_
#define DRAFT_APPLICATION_H_

#include "Gui.h"
#include "RemoteController.h"

template <class UI>
class DraftApplication {
 public:
  DraftApplication();

 private:
  UI ui;
};

template <>
DraftApplication<Gui>::DraftApplication() {
}

template <>
DraftApplication<RemoteController>::DraftApplication() {
  ui.start(QThread::LowPriority);
}

#endif // DRAFT_APPLICATION_H_
