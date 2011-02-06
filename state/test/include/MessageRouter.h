#ifndef MESSAGE_ROUTER_H_
#define MESSAGE_ROUTER_H_

#include <map>

class AddressedMessage;
class PlayerId;
class StateMachineComponentWrapper;

typedef std::pair<PlayerId, StateMachineComponentWrapper*> PlayerIdStateMachineWrapperPair;
typedef std::map<PlayerId, StateMachineComponentWrapper*> StateMachineVector;

class MessageRouter {
 public:
  void registerReceiver(const PlayerId& playerId, StateMachineComponentWrapper& stateMachineComponent);
  void send(const AddressedMessage& message) const;

 private:
  StateMachineVector stateMachineComponentWrappers;
};

#endif
