#include "PlayerId.h"

#include <QDataStream>

using std::ostream;

enum {
  NO_PLAYER_ID = 0xff,
  SERVER_PLAYER_ID = 0xfe,
  OWN_PLAYER_ID = 0xfd
};

PlayerId::PlayerId() : value(NO_PLAYER_ID) {
}

PlayerId::PlayerId(quint8 playerId) : value(playerId) {
}

bool operator<(const PlayerId& lhs, const PlayerId& rhs) {
  return lhs.value < rhs.value;
}

bool operator==(const PlayerId& lhs, const PlayerId& rhs) {
  return lhs.value == rhs.value;
}

bool operator!=(const PlayerId& lhs, const PlayerId& rhs) {
  return !(lhs == rhs);
}

ostream& operator<<(ostream& stream, const PlayerId& playerId) {
  switch (playerId.value) {
  case NO_PLAYER_ID:
    stream << "PlayerId[NONE]";
    break;
  case SERVER_PLAYER_ID:
    stream << "PlayerId[SERVER]";
    break;
  case OWN_PLAYER_ID:
    stream << "PlayerId[OWN]";
    break;
  default:
    stream << static_cast<unsigned int>(playerId.value);
  }
  return stream;
}

QDataStream& operator<<(QDataStream& stream, const PlayerId& playerId) {
  stream << playerId.value;
  return stream;
}
 
QDataStream& operator>>(QDataStream& stream, PlayerId& playerId) {
  stream >> (playerId.value);
  return stream;
}

const PlayerId PlayerId::NONE(NO_PLAYER_ID);
const PlayerId PlayerId::SERVER(SERVER_PLAYER_ID);
const PlayerId PlayerId::OWN(OWN_PLAYER_ID);
