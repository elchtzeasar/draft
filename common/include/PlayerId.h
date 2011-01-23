#ifndef PLAYER_ID_H_
#define PLAYER_ID_H_

#include <QtGlobal>
#include <QMetaType>

#include <iostream>

class PlayerId {
 public:
  PlayerId();
  PlayerId(quint8 playerId);

  static const PlayerId NONE;
  static const PlayerId SERVER;
  static const PlayerId OWN;

 private:
  quint8 value;

  friend bool operator<(const PlayerId& lhs, const PlayerId& rhs);
  friend bool operator==(const PlayerId& lhs, const PlayerId& rhs);
  friend bool operator!=(const PlayerId& lhs, const PlayerId& rhs);
  friend std::ostream& operator<<(std::ostream& stream, const PlayerId& playerId);
  friend QDataStream& operator<<(QDataStream& stream, const PlayerId& playerId);
  friend QDataStream& operator>>(QDataStream& stream, PlayerId& playerId);
};

Q_DECLARE_METATYPE(PlayerId);

bool operator<(const PlayerId& lhs, const PlayerId& rhs);
bool operator==(const PlayerId& lhs, const PlayerId& rhs);
bool operator!=(const PlayerId& lhs, const PlayerId& rhs);
std::ostream& operator<<(std::ostream& stream, const PlayerId& playerId);
QDataStream& operator<<(QDataStream& stream, const PlayerId& playerId);
QDataStream& operator>>(QDataStream& stream, PlayerId& playerId);

#endif // PLAYER_ID_H_
