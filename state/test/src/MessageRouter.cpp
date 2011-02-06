#include "MessageRouter.h"

#include "AddressHeader.h"
#include "AddressedMessage.h"
#include "PlayerId.h"
#include "StateMachineComponentWrapper.h"

void MessageRouter::registerReceiver(const PlayerId& playerId,
				     StateMachineComponentWrapper& stateMachineComponent) {
  stateMachineComponentWrappers.insert(PlayerIdStateMachineWrapperPair(playerId, &stateMachineComponent));
}

void MessageRouter::send(const AddressedMessage& message) const {
  const PlayerId& receiver(message.getHeader().getReceiverPlayerId());

  stateMachineComponentWrappers.find(receiver)->second->sendDataReceived(message);
}
