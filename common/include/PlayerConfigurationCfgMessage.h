#ifndef PLAYER_CONFIGURATION_CFG_MESSAGE_H_
#define PLAYER_CONFIGURATION_CFG_MESSAGE_H_

#include "Message.h"

#include <QString>

class PlayerConfigurationCfgMessage : public Message {
 public:
  PlayerConfigurationCfgMessage(const MessageNumber& messageNumber = MessageNumber::PLAYER_CONFIGURATION_CFG);
  PlayerConfigurationCfgMessage(const char* playerName);

  virtual Message* clone();
  static bool messageNumberIsAllowed(const MessageNumber& messageNumber);

  const char* getPlayerName() const;

  const int unused;
  char* playerName;

 private:
  PlayerConfigurationCfgMessage(const PlayerConfigurationCfgMessage&);
  PlayerConfigurationCfgMessage& operator=(PlayerConfigurationCfgMessage&);

  friend bool operator==(const PlayerConfigurationCfgMessage& lhs, const PlayerConfigurationCfgMessage& rhs);
  friend std::ostream& operator<<(std::ostream& stream, const PlayerConfigurationCfgMessage& message);
  friend QDataStream& operator<<(QDataStream& stream, const PlayerConfigurationCfgMessage& message);
  friend QDataStream& operator>>(QDataStream& stream, PlayerConfigurationCfgMessage& message);
};

bool operator==(const PlayerConfigurationCfgMessage& lhs, const PlayerConfigurationCfgMessage& rhs);
std::ostream& operator<<(std::ostream& stream, const PlayerConfigurationCfgMessage& message);
QDataStream& operator<<(QDataStream& stream, const PlayerConfigurationCfgMessage& message);
QDataStream& operator>>(QDataStream& stream, PlayerConfigurationCfgMessage& message);

#endif // PLAYER_CONFIGURATION_CFG_MESSAGE_H_
