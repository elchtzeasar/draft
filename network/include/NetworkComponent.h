#ifndef NETWORK_COMPONENT_H_
#define NETWORK_COMPONENT_H_

#include <QObject>

class NetworkComponent : public QObject {
  Q_OBJECT

 public:
  NetworkComponent();

 public slots:
  void hostDraftSlot(unsigned int port);
  void connectToDraftSlot();
};

#endif // NETWORK_COMPONENT_H_
