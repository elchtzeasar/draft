#ifndef CONFIGURATION_MANAGER_H_
#define CONFIGURATION_MANAGER_H_

#include <string>

class ConfigurationManager {
 public:
  ConfigurationManager(const std::string& filename);
  virtual ~ConfigurationManager();
  virtual void load();
  virtual void save() const;

  virtual const std::string& getPlayerName() const;
  virtual void setPlayerName(const std::string& playerName);
 private:
  ConfigurationManager(const ConfigurationManager&);
  ConfigurationManager& operator=(ConfigurationManager&);

  const std::string filename;
  std::string playerName;
};

#endif // CONFIGURATION_MANAGER_H_
