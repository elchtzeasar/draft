#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <string>

class ConfigurationManager {
 public:
  virtual ~ConfigurationManager() {}

  virtual const std::string& getPlayerName() const = 0;
  virtual void setPlayerName(const std::string& playerName) = 0;
};

#endif // CONFIGURATION_MANAGER_H_
