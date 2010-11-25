#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <string>

class ConfigurationManager {
 public:
  virtual ~ConfigurationManager() {}
  virtual void load() = 0;
  virtual void save() const = 0;

  virtual const std::string& getPlayerName() const = 0;
  virtual void setPlayerName(const std::string& playerName) = 0;
};

#endif // CONFIGURATION_MANAGER_H_
