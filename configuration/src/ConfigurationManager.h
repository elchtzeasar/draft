#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <string>

class ConfigurationManager {
 public:
  ConfigurationManager(const std::string& filename);
  void load();
  void save() const;

  const std::string& getPlayerName() const;
  void setPlayerName(const std::string& playerName);
 private:
  ConfigurationManager(const ConfigurationManager&);
  ConfigurationManager& operator=(ConfigurationManager&);

  const std::string filename;
  std::string playerName;
};

#endif // CONFIGURATION_MANAGER_H_
