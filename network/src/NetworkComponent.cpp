#include "NetworkComponent.h"

#include <iostream>

using std::cout;
using std::endl;

NetworkComponent::NetworkComponent() {}

void NetworkComponent::hostDraftSlot(unsigned int port) {
  cout << "NetworkComponent::hostDraft(" << port << ')' << endl;
}

void NetworkComponent::connectToDraftSlot() {
  cout << "NetworkComponent::connectToDraft()" << endl;
}
