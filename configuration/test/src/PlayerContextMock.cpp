#include "PlayerContextMock.h"

bool operator==(const PlayerContext& lhs, const PlayerContext& rhs) {
  return &lhs == &rhs;
}

std::ostream& operator<<(std::ostream& stream, const PlayerContext& playerContext) {
  stream << "PlayerContext[0x" << std::hex << &playerContext << "]";
  return stream;
}
