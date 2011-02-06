#ifndef PLAYER_NAME_CFG_MESSAGE_H_
#define PLAYER_NAME_CFG_MESSAGE_H_

#include "Message.h"

#include <QString>

class PlayerNameCfgMessage : public Message {
 public:
  PlayerNameCfgMessage(quint16 messageNumber = PLAYER_NAME_CFG);
  PlayerNameCfgMessage(const char* playerName);

  virtual Message* clone();
  static bool messageNumberIsAllowed(quint16 messageNumber);

  const char* getPlayerName() const;

  const int unused;
  char* playerName;

 private:
  PlayerNameCfgMessage(const PlayerNameCfgMessage&);
  PlayerNameCfgMessage& operator=(PlayerNameCfgMessage&);

  friend bool operator==(const PlayerNameCfgMessage& lhs, const PlayerNameCfgMessage& rhs);
  friend std::ostream& operator<<(std::ostream& stream, const PlayerNameCfgMessage& message);
  friend QDataStream& operator<<(QDataStream& stream, const PlayerNameCfgMessage& message);
  friend QDataStream& operator>>(QDataStream& stream, PlayerNameCfgMessage& message);
};

bool operator==(const PlayerNameCfgMessage& lhs, const PlayerNameCfgMessage& rhs);
std::ostream& operator<<(std::ostream& stream, const PlayerNameCfgMessage& message);
QDataStream& operator<<(QDataStream& stream, const PlayerNameCfgMessage& message);
QDataStream& operator>>(QDataStream& stream, PlayerNameCfgMessage& message);

#endif // PLAYER_NAME_CFG_MESSAGE_H_
