#ifndef CONNECTION_LISTENER_MOCK_H_
#define CONNECTION_LISTENER_MOCK_H_

#include "ConnectionListener.h"

class ConnectionListenerMock : public ConnectionListener {
 public:
  MOCK_METHOD1(listen, void(unsigned int port));

 protected slots:
  MOCK_METHOD0(acceptConnection, void());
};

#endif // CONNECTION_LISTENER_MOCK_H_
